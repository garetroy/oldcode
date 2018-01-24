#include "boundingbox.h"

Boundingbox::Boundingbox(void)
{
    for(int i = 0; i < 3; i++){
        max[i] = 0;
        min[i] = 0;
    }
    
    initialized = true;
}

void
Boundingbox::SetBoundingBox(double* _x, double* _y, double* _z)
{
    if(_x[0] > _x[1]){
        max[0] = _x[0];
        min[0] = _x[1];
    } else {
        min[0] = _x[0];
        max[0] = _x[1];
    }

    if(_y[0] > _y[1]){
        max[1] = _y[0];
        min[1] = _y[1];
    } else {
        min[1] = _y[0];
        max[1] = _y[1]; 
    } 

    if(_z[0] > _z[1]){
        max[2] = _z[0];
        min[2] = _z[1];
    } else {
        min[2] = _z[0];
        max[2] = _z[1]; 
    }

    initialized = true;

}

void 
Boundingbox::ExpandBoundingBox(Boundingbox *_box)
{
    if(!IsInitialized() || !_box->IsInitialized()){
        std::cerr << "ExpandBoundingBox() failed, Bounding Box not initialized" << std::endl;
        exit(EXIT_FAILURE);
    }
    double temp_max[3];
    double temp_min[3];

    _box->GetMax(temp_max);
    _box->GetMin(temp_min);
    for(int i = 0; i < 3; i++){
        if(temp_max[i] > max[i])
            max[i] = temp_max[i];
    
        if(temp_min[i] < min[i])
            min[i] = temp_min[i];
    }

}

void
Boundingbox::GetMax(double* maxs)
{
    if(initialized){
        memcpy(maxs,max,sizeof(double)*3);
    } else {
        std::cerr << "GetMax() failed, Bounding Box not initialized" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void
Boundingbox::GetMin(double* mins)
{
    if(initialized){
        memcpy(mins,min,sizeof(double)*3);
    } else {
        std::cerr << "GetMin() failed, Bounding Box not initialized" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void
Boundingbox::Print(std::ostream &o)
{
    o << "Max:" << max[0] << "," << max[1] << "," << max[2] << std::endl;
    o << "Min:" << min[0] << "," << min[1] << "," << min[2] << std::endl;
}

bool
Boundingbox::IsInitialized(void)
{
    return initialized;
}

char
Boundingbox::LongestAxis(void)
{
   double maxnum = fmax(fmax(max[0],max[1]),max[2]);
    
   if(maxnum == max[0])
        return 'x';

   if(maxnum == max[1])
        return 'y'; 

   return 'z';
}

bool
Boundingbox::Hit(Ray &ray)
{
    double tmin, tmax, tymin, tymax, tzmin, tzmax, t;
    double bounds[2][3] = {{min[0],min[1],min[2]},{max[0],max[1],max[2]}};
    
    return true;

    tmin  = (bounds[ray.sign[0]][0] - ray.origin.x) * ray.inversedir.x;
    tmax  = (bounds[1-ray.sign[0]][0] - ray.origin.x) * ray.inversedir.x;
    tymin = (bounds[ray.sign[1]][1] - ray.origin.y) * ray.inversedir.y;
    tymax = (bounds[1-ray.sign[1]][0] - ray.origin.y) * ray.inversedir.y;

    if((tmin > tymax) || (tymin > tmax))
        return false;

    if(tymin > tmin)
        tmin = tymin;
    if(tymax < tmax)
        tmax = tymax;

    tzmin = (bounds[ray.sign[2]][2] - ray.origin.z) * ray.inversedir.z;
    tzmax = (bounds[1-ray.sign[2]][2] - ray.origin.z) * ray.inversedir.z;

    if((tmin > tzmax) || (tzmin > tmax))
        return false;
    
    if(tzmin > tmin)
        tmin = tzmin;
    if(tzmax < tmax)
        tmax = tzmax;

    t = tmin;

    if(t < 0) {
        t = tmax;
        if(t<0)
            return false;
    }
    return true;
}
