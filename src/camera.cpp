#include "camera.hpp"

Camera::Camera(int image_width, int image_height, float viewport_height, float focal_length) {
    float aspect_ratio = float(image_width) / float(image_height);
    float viewport_width = aspect_ratio * viewport_height;

    origin = Vec3{0.0f, 0.0f, 0.0f};
    horizontal = Vec3{viewport_width, 0.0f, 0.0f};
    vertical = Vec3{0.0f, viewport_height, 0.0f};
    lower_left_corner = origin - horizontal / 2.0f - vertical / 2.0f - Vec3{0.0f, 0.0f, focal_length};
}

Ray Camera::get_ray(float u, float v) const {
    Vec3 direction = lower_left_corner + horizontal * u + vertical * v - origin;
    return Ray(origin, direction);
}