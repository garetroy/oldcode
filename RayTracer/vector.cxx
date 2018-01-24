#include "vector.h"

Vec3::Vec3(void)
{
    x = 0;
    y = 0;
    z = 0;
} 

Vec3::Vec3(double _x)
{
    x = _x;
    y = _x;
    z = _x;
}

Vec3::Vec3(double _x, double _y, double _z)
{
    x = _x;
    y = _y;
    z = _z;
}

void
Vec3::Print(ostream &o)
{
    o << "[" << x << " " << y << " " << z << "]" << endl;
}

