#ifndef _RAY_H_
#define _RAY_H_

#include "vector.h"

class Ray{

    public:
        Vec3   origin;
        Vec3   direction;
        Vec3   inversedir;
        int    sign[3];
        double tmin;
        double t;
    
               Ray(void);
               Ray(Vec3 *_origin, Vec3 *_direction, double _tmin);
        void   Update(void);
};
#endif
