#ifndef RAYTRACER_SPHERE_HPP
#define RAYTRACER_SPHERE_HPP

#include "Hittable.hpp"
#include "vec3.hpp"
#include <cmath>

struct Sphere : Hittable {
    Vec3 centre;
    float radius;
    Vec3 color;

    Sphere(const Vec3 &centre, float radius, const Vec3 &color);

    bool hit(
        const Ray &ray,
        float t_min,
        float t_max,
        HitRecord &rec
    ) const override;
};

#endif // RAYTRACER_SPHERE_HPP