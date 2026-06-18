#ifndef RAYTRACER_HITTABLE_HPP
#define RAYTRACER_HITTABLE_HPP

#include "ray.hpp"
#include "vec3.hpp"

struct HitRecord {
    Vec3 point;
    Vec3 normal;
    Vec3 color;
    float t;
};

struct Hittable {
    virtual bool hit(
        const Ray &ray,
        float t_min,
        float t_max,
        HitRecord &rec
    ) const = 0;

    virtual ~Hittable() = default;
};

#endif // RAYTRACER_HITTABLE_HPP