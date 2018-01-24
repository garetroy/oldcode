#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include <cmath>
#include <cstdio>
#include <iostream>

#include "vector.h"
#include "boundingbox.h"
#include "screen.h"
#include "ray.h"

using namespace std;

class Triangle{

    public:
        Vec3         coord1; //left
        Vec3         coord2; //right
        Vec3         coord3; //middle
        Vec3         colors[3];
        Boundingbox  bbox;

                     Triangle();
                     Triangle(Vec3& _coord1, Vec3& _coord2, Vec3& _coord3, Vec3* _colors);
        void         InitBoundingBox(void);
        Boundingbox* GetBoundingBox(void);
        void         GetMidPoint(Vec3& mid);
        bool         Hit(Ray& ray, Screen& screen, double& u, double& v);        
        void         Print(ostream &o);
};

#endif
