#ifndef RAY_H
#define RAY_H
#include "vec.h"

class Ray{
    public:
        Vec3f orig;
        Vec3f dir;
        double t;
    public:
        Ray(const Vec3f& origin, const Vec3f& direction, const double _t = 0) : orig(origin), dir(direction), t(_t){}

        Vec3f trace(double t) const{
            return orig + dir * t;
        }
   
};
#endif