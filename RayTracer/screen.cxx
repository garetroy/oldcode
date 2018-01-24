#include "screen.h"

inline 
float deg2rad(const float &deg) 
{ return deg * M_PI / 180; } 

Screen::Screen(const int _height, const int _width, const double _fov)
{
    height       = _height;
    width        = _width; 
    fov          = 51.52;
    scale        = 300;//1/tan(deg2rad(fov * 0.5)); 
    aspectratio  = width/height;
    framebuffer  = new Vec3[width*height];
    pixelpointer = framebuffer;
}

Screen::~Screen(void)
{
    delete [] framebuffer;
}

void
Screen::DrawTriangle(double u, double v, Vec3 *colors)
{
    *pixelpointer = u * colors[0] + v * colors[1] + (1 - u - v) * colors[2];
}
