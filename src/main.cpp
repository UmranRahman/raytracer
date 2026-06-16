#include <cfloat>
#include <iostream>
#include <memory>
#include <fstream>
#include <algorithm>
#include "camera.hpp"
#include "world.hpp"
#include "sphere.hpp"

void write_color(std::ostream &out, const Vec3 &color) {
    int r = static_cast<int>(255.999f * color.x);
    int g = static_cast<int>(255.999f * color.y);
    int b = static_cast<int>(255.999f * color.z);
    out << r << ' ' << g << ' ' << b << '\n';
}

Vec3 ray_color(const Ray &r, const World &world) {
    HitRecord rec;
    if (world.hit(r, 0.001f, FLT_MAX, rec)) {
        Vec3 N = normalize(rec.normal);
        return 0.5f * Vec3{N.x + 1.0f, N.y + 1.0f, N.z + 1.0f};
    }

    Vec3 unit_dir = normalize(r.direction);
    float t2 = 0.5f * (unit_dir.y + 1.0f);
    return Vec3{1.0f, 1.0f, 1.0f} * (1.0f - t2) + Vec3{0.5f, 0.7f, 1.0f} * t2;
}

// helper to convert float color [0,1] -> byte
static unsigned char to_byte(float v) {
    v = std::max(0.0f, std::min(1.0f, v));
    return static_cast<unsigned char>(255.999f * v);
}

int main() {
    const int image_width = 400;
    const int image_height = 225;

    Camera camera(image_width, image_height, 2.0f, 1.0f);
    World world;
    Sphere sphere(Vec3{0.0f, 0.0f, -1.0f}, 0.5f);
    world.add(&sphere);

    std::ofstream out("image.ppm", std::ios::binary);
    out << "P6\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            float u = float(i) / (image_width - 1);
            float v = float(j) / (image_height - 1);
            Ray r = camera.get_ray(u, v);
            Vec3 color = ray_color(r, world);
            unsigned char pixel[3] = {
                to_byte(color.x),
                to_byte(color.y),
                to_byte(color.z)
            };
            out.write(reinterpret_cast<char*>(pixel), 3);
        }
    }
    out.close();
    return 0;
}