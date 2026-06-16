#ifndef RAYTRACER_CAMERA_HPP
#define RAYTRACER_CAMERA_HPP

#include "vec3.hpp"
#include "ray.hpp"

struct Camera {
    Vec3 origin;
    Vec3 lower_left_corner;
    Vec3 horizontal;
    Vec3 vertical;

    Camera(int image_width, int image_height, float viewport_height, float focal_length);

    Ray get_ray(float u, float v) const;
};

#endif // RAYTRACER_CAMERA_HPP