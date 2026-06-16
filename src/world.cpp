#include "world.hpp"

void World::add(Hittable *object) {
    objects.push_back(object);
}

bool World::hit(const Ray &ray, float t_min, float t_max, HitRecord &rec) const {
    bool any_hit = false;
    float closest_so_far = t_max;
    HitRecord temp_rec;

    for (auto object : objects) {
        if (object->hit(ray, t_min, closest_so_far, temp_rec)) {
            any_hit = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return any_hit;
}