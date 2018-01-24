/*
    Created by Garett Roberts
    A lot of this code was derived from https://www.scratchapixel.com/code.php?id=22&origin=/lessons/mathematics-physics-for-computer-graphics/geometry
*/

#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>

using namespace std;

class Vec3{
    
    public:
        
               Vec3(void);
               Vec3(double _x);
               Vec3(double _x, double _y, double _z);

        inline Vec3    operator +  (const Vec3 &v) const;
        inline Vec3    operator -  (const Vec3 &v) const;
        inline Vec3    operator *  (const Vec3 &v) const;
        inline Vec3    operator *  (const double &v) const;
        inline Vec3&   operator *= (const double &v);
        inline Vec3&   operator /= (const double &v);
        inline double& operator [] (uint8_t i);

        inline double DotProduct   (const Vec3 &v) const;
        inline Vec3   CrossProduct (const Vec3 &v) const;
        inline double Normal       (void)          const;
        inline double Length       (void)          const; 
        
        inline Vec3& Normalize(void);
               void  Print(ostream &o);

        inline friend Vec3 operator * (const double &c, const Vec3 &v)
        {
            return Vec3(v.x * c, v.y * c, v.z * c);
        }
    
        inline friend Vec3 operator / (const double &c, const Vec3 &v)
        {
            return Vec3(c / v.x, c / v.y, c / v.z);
        }

        inline friend void swap(Vec3 &a, Vec3 &b)
        {
            using std::swap;
            swap(a.x,b.x);
            swap(a.y,b.y);
            swap(a.z,b.z);
        }

        double x, y, z;
};

inline Vec3
Vec3::operator+(const Vec3 &v) const
{
    return Vec3(x + v.x, y + v.y, z + v.z);
}

inline Vec3
Vec3::operator-(const Vec3 &v) const 
{
    return Vec3(x - v.x, y - v.y, z - v.z);
}

inline Vec3
Vec3::operator*(const double &v) const 
{
    return Vec3(x * v, y * v, z * v);
}

inline Vec3
Vec3::operator*(const Vec3 &v) const 
{
    return Vec3(x * v.x, y * v.y, z * v.z);
}

inline Vec3&
Vec3::operator*=(const double &v) 
{
    x *= v;
    y *= v; 
    z *= v;
    return *this;
}

inline Vec3&
Vec3::operator/=(const double &v)
{
    x /= v;
    y /= v;
    z /= v;
    return *this;
}

inline double&
Vec3::operator[](uint8_t i) 
{
    return (&x)[i];
}

inline double
Vec3::DotProduct(const Vec3 &v) const 
{
    return (x * v.x + y * v.y + z * v.z);
}    

inline Vec3
Vec3::CrossProduct(const Vec3 &v) const 
{
    return Vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

inline double
Vec3::Normal(void) const 
{
    return (x*x + y*y + z*z);
}

inline Vec3&
Vec3::Normalize(void) 
{
    double norm = Normal();
    
    x *= (1/ sqrt(norm));
    y *= (1/ sqrt(norm));
    z *= (1/ sqrt(norm));
    
    return *this;
}
#endif
