#ifndef _BOUNDINGBOX_H_
#define _BOUNDINGBOX_H_

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cmath>

#include "ray.h"

using namespace std;

class Boundingbox{

    public:
             Boundingbox(void);
        void SetBoundingBox(double* _x,double* _y, double* _z);
        void ExpandBoundingBox(Boundingbox *_box);
        void GetMax(double* maxs);
        void GetMin(double* mins);
        bool IsInitialized(void);
        void Print(std::ostream &o);
        char LongestAxis(void);
        bool Hit(Ray &ray);

    private:
        double max[3]; //x,y,z
        double min[3]; //x,y,z
        bool   initialized;
};

#endif
