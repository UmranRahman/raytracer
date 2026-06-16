#ifndef RAYTRACER_RAY_HPP
#define RAYTRACER_RAY_HPP

#include "vec3.hpp"

struct Ray {
    Vec3 origin;
    Vec3 direction;
    
    Ray (const Vec3 &origin, const Vec3 &direction);

    Vec3 at(float t) const;
};
#endif // RAYTRACER_RAY_HPP