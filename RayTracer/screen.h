#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <cmath> 
#include <cstdio>

#include "vector.h"

class Screen{

    public:
        Screen(const int _height, const int _width, const double _fov);
       ~Screen(void);
    
    void DrawTriangle(double u, double v, Vec3 *colors); 

    Vec3   *framebuffer; 
    Vec3   *pixelpointer;
    double fov, scale, aspectratio;
    int    height, width;
};

#endif
