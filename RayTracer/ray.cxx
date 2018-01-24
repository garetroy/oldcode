#include "ray.h"

Ray::Ray(void)
{
    origin    = Vec3(0,0,0);
    direction = Vec3(0,0,0);
    tmin      = 0;
    t         = 0; 
}

Ray::Ray(Vec3 *_origin, Vec3 *_direction, double _tmin)
{
    origin    = *_origin;
    direction = *_direction;
    tmin      = _tmin;
    t         = 0;
    inversedir    = 1 / direction; 
    sign[0]   = (inversedir.x < 0);
    sign[1]   = (inversedir.y < 0);
    sign[2]   = (inversedir.z < 0);
}

void
Ray::Update(void)
{
    inversedir    = 1 / direction; 
    sign[0]   = (inversedir.x < 0);
    sign[1]   = (inversedir.y < 0);
    sign[2]   = (inversedir.z < 0);
}
