#include "sphere.hpp"

Sphere::Sphere(const Vec3 &centre, float radius, const Vec3 &color)
    : centre(centre), radius(radius), color(color) {
}

bool Sphere::hit(const Ray &ray, float t_min, float t_max, HitRecord &rec) const {
    Vec3 oc = ray.origin - centre;
    float a = dot(ray.direction, ray.direction);
    float half_b = dot(oc, ray.direction);
    float c = dot(oc, oc) - radius * radius;
    float discriminant = half_b * half_b - a * c;

    if (discriminant < 0.0f) return false;

    float root = std::sqrt(discriminant);

    float t = (-half_b - root) / a;
    if (t < t_min || t > t_max) {
        t = (-half_b + root) / a;
        if (t < t_min || t > t_max) {
            return false;
        }
    }

    rec.t = t;
    rec.point = ray.at(t);
    rec.normal = normalize(rec.point - centre);
    rec.color = color;
    return true;
}