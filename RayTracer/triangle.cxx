#include "triangle.h"

double
Lerp(double start, double end, double proportion)
{
    return start+(end-start)*proportion;
}

Triangle::Triangle(void)
{
    coord1 = Vec3(0,0,0);
    coord2 = Vec3(0,0,0);
    coord3 = Vec3(0,0,0);

    for(int i = 0; i < 3; i++)
        colors[i] = Vec3(0,0,0);
    
    InitBoundingBox();
}

Triangle::Triangle(Vec3& _coord1, Vec3& _coord2, Vec3& _coord3, Vec3* _colors)
{
    coord1 = _coord1;
    coord2 = _coord2;
    coord3 = _coord3;

    for(int i = 0; i < 3; i++)
        colors[i] = _colors[i];
 
    InitBoundingBox();
}

void
Triangle::InitBoundingBox(void)
{
    double _x[2] = {0,0};
    double _y[2] = {0,0};
    double _z[2] = {0,0};

    _x[0] = fmax(fmax(coord1[0],coord2[0]),coord3[0]);
    _x[1] = fmin(fmin(coord1[0],coord2[0]),coord3[0]);
    _y[0] = fmax(fmax(coord1[1],coord2[1]),coord3[1]); 
    _y[1] = fmin(fmin(coord1[1],coord2[1]),coord3[1]);
    _z[0] = fmax(fmax(coord1[2],coord2[2]),coord3[2]); 
    _z[1] = fmin(fmin(coord1[0],coord2[1]),coord3[2]);
    bbox.SetBoundingBox(_x,_y,_z);
}

Boundingbox*
Triangle::GetBoundingBox(void)
{
    if(bbox.IsInitialized())
        return &bbox;

    InitBoundingBox();
    return &bbox;
}

void
Triangle::GetMidPoint(Vec3& mid)
{
    mid[0] = (coord1[0] + coord2[0] + coord3[0]) / 3.0;
    mid[1] = (coord1[1] + coord2[1] + coord3[1]) / 3.0;
    mid[2] = (coord3[2] + coord3[2] + coord3[2]) / 3.0;
}

bool
Triangle::Hit(Ray& ray, Screen& screen, double& u, double& v)
{
    /*This method utilizes Moller Trubore algorithm */

    double kEpsilon = 1e-8;

    Vec3 vec1 = coord2 - coord1;
    Vec3 vec2 = coord3 - coord1;

    Vec3 P     = ray.direction.CrossProduct(vec2);

    double det = vec1.DotProduct(P); 
    if(det < kEpsilon) return false;

    double invDet = 1/det;

    Vec3 tvec = ray.origin - coord1;
         u    = tvec.DotProduct(P) * invDet;
   
    if(u < 0 || u > 1) return false;

    Vec3 q = tvec.CrossProduct(vec1);
         v = ray.direction.DotProduct(q) * invDet;

    if(v < 0 || u + v > 1) return false;
    ray.t = vec2.DotProduct(q) * invDet;

    return true;
}

void
Triangle::Print(ostream &o)
{
    o << "---Triangle Coordinates---" << endl;
    
    coord1.Print(o);
    coord2.Print(o);
    coord3.Print(o);

    o << "---Triangle Colors---" << endl;
    
    for(int i = 0; i < 3; i++)
        colors[i].Print(o);
}
