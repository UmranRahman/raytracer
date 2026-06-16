#ifndef RAYTRACER_WORLD_HPP
#define RAYTRACER_WORLD_HPP

#include <vector>
#include "hittable.hpp"
#include "ray.hpp"

struct World {
    std::vector<Hittable*> objects;

    void add(Hittable *object);
    bool hit(const Ray &ray, float t_min, float t_max, HitRecord &rec) const;
};

#endif // RAYTRACER_WORLD_HPP