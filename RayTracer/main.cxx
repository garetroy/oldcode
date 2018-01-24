#include "triangle.h" 
#include "screen.h"
#include "matrix.h"
#include "boundingbox.h"
#include "kdtree.h"
#include "vector.h"
#include "ray.h" 
//#include <omp.h>

#include <cstdio> 
#include <ctime>
#include <cstdlib> 
#include <iostream> 
#include <fstream> 
#include <cmath> 

#include <vtkDataSet.h>
#include <vtkImageData.h>
#include <vtkPNGWriter.h>
#include <vtkPointData.h>
#include <vtkPolyData.h>
#include <vtkPolyDataReader.h>
#include <vtkPoints.h>
#include <vtkUnsignedCharArray.h>
#include <vtkFloatArray.h>
#include <vtkCellArray.h>
#include <vtkDoubleArray.h>
 
 
inline 
float clamp(const float &lo, const float &hi, const float &v) 
{ return std::max(lo, std::min(hi, v)); } 


vtkImageData *
NewImage(int width, int height)
{
    vtkImageData *img = vtkImageData::New();
    img->SetDimensions(width, height, 1);
    img->AllocateScalars(VTK_UNSIGNED_CHAR, 3);

    return img;
}

void
WriteImage(vtkImageData *img, const char *filename, int k)
{
    std::string full_filename = filename;
    std::string number        = std::to_string(k);
    full_filename += number;
    full_filename += ".png";
    vtkPNGWriter *writer = vtkPNGWriter::New();
    writer->SetInputData(img);
    writer->SetFileName(full_filename.c_str());
    writer->Write();
    writer->Delete();
}

std::vector<Triangle*>
GetTriangles(void)
{
    vtkPolyDataReader *rdr = vtkPolyDataReader::New();
    rdr->SetFileName("proj1d_geometry.vtk");
    cerr << "Reading" << endl;
    rdr->Update();
    cerr << "Done reading" << endl;
    if (rdr->GetOutput()->GetNumberOfCells() == 0)
    {
        cerr << "Unable to open file!!" << endl;
        exit(EXIT_FAILURE);
    }
    vtkPolyData *pd = rdr->GetOutput();
    int numTris = pd->GetNumberOfCells();
    vtkPoints *pts = pd->GetPoints();
    vtkCellArray *cells = pd->GetPolys();
    vtkFloatArray *var = (vtkFloatArray *) pd->GetPointData()->GetArray("hardyglobal");
    float *color_ptr = var->GetPointer(0);
    std::vector<Triangle*> tris(numTris);
    vtkIdType npts;
    vtkIdType *ptIds;
    int idx;
    for (idx = 0, cells->InitTraversal() ; cells->GetNextCell(npts, ptIds) ; idx++)
    {
        if (npts != 3)
        {
            cerr << "Non-triangles!! ???" << endl;
            exit(EXIT_FAILURE);
        }
        tris[idx] = new Triangle();
        tris[idx]->coord1 = Vec3(pts->GetPoint(ptIds[0])[0],pts->GetPoint(ptIds[0])[1],pts->GetPoint(ptIds[0])[2]);
        tris[idx]->coord2 = Vec3(pts->GetPoint(ptIds[1])[0],pts->GetPoint(ptIds[1])[1],pts->GetPoint(ptIds[1])[2]);
        tris[idx]->coord3 = Vec3(pts->GetPoint(ptIds[2])[0],pts->GetPoint(ptIds[2])[1],pts->GetPoint(ptIds[2])[2]);
        // 1->2 interpolate between light blue, dark blue
        // 2->2.5 interpolate between dark blue, cyan
        // 2.5->3 interpolate between cyan, green
        // 3->3.5 interpolate between green, yellow
        // 3.5->4 interpolate between yellow, orange
        // 4->5 interpolate between orange, brick
        // 5->6 interpolate between brick, salmon
        double mins[7] = { 1, 2, 2.5, 3, 3.5, 4, 5 };
        double maxs[7] = { 2, 2.5, 3, 3.5, 4, 5, 6 };
        unsigned char RGB[8][3] = { { 71, 71, 219 }, 
                                    { 0, 0, 91 },
                                    { 0, 255, 255 },
                                    { 0, 128, 0 },
                                    { 255, 255, 0 },
                                    { 255, 96, 0 },
                                    { 107, 0, 0 },
                                    { 224, 76, 76 } 
                                  };
        for (int j = 0 ; j < 3 ; j++)
        {
            float val = color_ptr[ptIds[j]];
            int r;
            for (r = 0 ; r < 7 ; r++)
            {
                if (mins[r] <= val && val < maxs[r])
                    break;
            }
            if (r == 7)
            {
                cerr << "Could not interpolate color for " << val << endl;
                exit(EXIT_FAILURE);
            }
            double proportion = (val-mins[r]) / (maxs[r]-mins[r]);
            tris[idx]->colors[j] = Vec3((RGB[r][0]+proportion*(RGB[r+1][0]-RGB[r][0]))/255.0, (RGB[r][1]+proportion*(RGB[r+1][1]-RGB[r][1]))/255.0, (RGB[r][2]+proportion*(RGB[r+1][2]-RGB[r][2]))/255.0);
        }
    }

    return tris;
}

/*std::vector<Triangle*>
GetTriangles(void)
{
   std::vector<Triangle*> rv(100);

   unsigned char colors[6][3] = { {255,128,0}, {255, 0, 127}, {0,204,204}, 
                                  {76,153,0}, {255, 204, 204}, {204, 204, 0}};
   for (int i = 0 ; i < 100 ; i++)
   {
       int idxI = i%10;
       int posI = idxI*100;
       int idxJ = i/10;
       int posJ = idxJ*100;
       int firstPt = (i%3);
       rv[i] = new Triangle();
       if (i == 50){
           rv[i]->coord1 = Vec3(-10,posJ,-4);
       } else {
           rv[i]->coord1 = Vec3(posI,posJ,-4);
       }
       rv[i]->coord2 = Vec3(posI+99,posJ,-4);
       if (i == 95){
          rv[i]->coord3 = Vec3(posI+i,1050,-4);
       } else {
          rv[i]->coord3 = Vec3(posI+i,posJ+10*(idxJ+1),-4);
       }
       rv[i]->colors[0] = Vec3(colors[i%6][0],colors[i%6][1],colors[i%6][2]);
       rv[i]->colors[1] = Vec3(colors[i%6][0],colors[i%6][1],colors[i%6][2]);  
       rv[i]->colors[2] = Vec3(colors[i%6][0],colors[i%6][1],colors[i%6][2]);  
   }

   return rv;
}*/


int main()
{
    Vec3 v0(-1, -1, -4.3);
    Vec3 v1( 1, -1.5, -4.3);
    Vec3 v2( 0,  1, -4.3);
    Vec3 v22(10, -1, -3);
    Vec3 v12( 1, -1.5, -5);
    Vec3 v02( 0,  1, -5);


    Vec3 cols[3] = {Vec3(0.6, 0.4, 0.1), Vec3(0.1, 0.5, 0.3), Vec3(0.1, 0.3, 0.7)};
    Vec3 cols2[3] = {Vec3(0.9, 0.1, 0.2), Vec3(0.3, 0.0, 0.1), Vec3(0.1, 0.9, 0.3)};
   
    Triangle *ourtriangle  = new Triangle(v0,v1,v2,cols);
    Triangle *ourtriangle2 = new Triangle(v02,v12,v22,cols2);
    Screen   screen        = Screen(1000,1000,52);
    Ray      ray           = Ray();    
    double   u, v, x, y;
    int      i,k,j;
    int      loc = 0;
    
    std::vector<Triangle*> tris = GetTriangles();
   // std::vector<Triangle*> tris;
//    tris.push_back(ourtriangle);
    //tris.push_back(ourtriangle2);

    Kdnode *kroot;
    kroot = kroot->Build(tris);
    clock_t start = clock(); 
    cerr << "KDtree built" << endl;
    //#pragma omp parallel for collapse(2) private(j,i,u,v,x,y) firstprivate(loc,ray,ourtriangle) shared(screen,cerr)
    for(j = 0; j < screen.height; ++j) {
        for (i = 0; i < screen.width; ++i) {
            x      = (2 * (i + 0.5) / screen.width) * screen.aspectratio * screen.scale;
            y      = (2 - 2 * (j + 0.5) / screen.height) * screen.scale;
            ray.direction =  Vec3(x, y, -1);
            ray.direction.Normalize();
            ray.Update();
            kroot->Hit(kroot,ray,screen,u,v,y);

            //for(int k = 0; k < tris.size(); k++){
            //    if(tris[k]->Hit(ray,screen,u,v))
            //        screen.DrawTriangle(v,y,tris[k]->colors); 
           // }
            /*if(ourtriangle.Hit(ray,screen,u,v))
                screen.DrawTriangle(loc,v,y,ourtriangle.colors);
    
            if(ourtriangle2.Hit(ray,screen,u,v))
                screen.DrawTriangle(loc,v,y,ourtriangle2.colors);
            */
        screen.pixelpointer++;
        }
        if(j != 0 && j%100 == 0)
            cerr << ".";
    }   
    cerr << endl << ((clock() - start) / (double) CLOCKS_PER_SEC) << endl;
    
    cerr << "Calculated...Creating image" << endl;
    std::ofstream ofs("./out.ppm", std::ios::out | std::ios::binary);
    ofs << "P6\n" << screen.width << " " << screen.height << "\n255\n";
    //#pragma omp parallel for schedule(auto) private(i) num_threads(1)
    for (i = 0; i < screen.height * screen.width; ++i) {
        char r = (char)(255 * clamp(0, 1, screen.framebuffer[i].x));
        char g = (char)(255 * clamp(0, 1, screen.framebuffer[i].y));
        char b = (char)(255 * clamp(0, 1, screen.framebuffer[i].z));
        ofs << r << g << b;
    }

    ofs.close();

    cerr << "Done" << endl;
    return 0;
}
