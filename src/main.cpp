#include <cstdio>
#include <cstdlib>
#include <cmath>

#include <cfloat>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

#include "camera.hpp"
#include "world.hpp"
#include "sphere.hpp"
#include "vec3.hpp"

void write_color(std::ostream &out, const Vec3 &color) {
    int r = static_cast<int>(255.999f * std::max(0.0f, std::min(1.0f, color.x)));
    int g = static_cast<int>(255.999f * std::max(0.0f, std::min(1.0f, color.y)));
    int b = static_cast<int>(255.999f * std::max(0.0f, std::min(1.0f, color.z)));
    out << r << ' ' << g << ' ' << b << '\n';
}

Vec3 unpackRGB(unsigned int packedRGB) {
    unsigned int r = (packedRGB >> 16) & 0xFF;
    unsigned int g = (packedRGB >> 8) & 0xFF;
    unsigned int b = packedRGB & 0xFF;
    return Vec3{r / 255.0f, g / 255.0f, b / 255.0f};
}

int compareColor(const void *a, const void *b) {
    int a1 = 0, b1 = 0;
    for (size_t i = 0; i < sizeof(int); i++) {
        a1 |= (*((unsigned char*)a + i) & 0x0F) << (i * 8);
        b1 |= (*((unsigned char*)b + i) & 0x0F) << (i * 8);
    }
    return (a1 < b1) ? -1 :
            (b1 < a1) ? 1 :
            (*((int*)a) < *((int*)b)) ? -1 :
            (*((int*)a) > *((int*)b)) ? 1 : 0;
}

bool in_shadow(const Ray &shadow_ray, const World &world, float max_t) {
    HitRecord temp;
    return world.hit(shadow_ray, 0.001f, max_t, temp);
}

Vec3 shaded_color(const HitRecord &rec, const Vec3 &light_pos, float light_brightness, const World &world) {
    Vec3 to_light = normalize(light_pos - rec.point);
    float dist2 = distance2(light_pos, rec.point);
    float intensity = light_brightness * std::max(0.0f, dot(to_light, rec.normal)) / dist2;
    intensity = std::min(1.0f, intensity);

    Ray shadow_ray(rec.point + rec.normal * 0.001f, to_light);
    float light_distance = std::sqrt(dist2);
    if (in_shadow(shadow_ray, world, light_distance)) {
        intensity *= 0.1f;
    }

    return rec.color * intensity;
}

Vec3 ray_color(const Ray &r, const World &world, const Vec3 &background_color, const Vec3 &light_pos, float light_brightness) {
    HitRecord rec;
    if (world.hit(r, 0.001f, FLT_MAX, rec)) {
        return shaded_color(rec, light_pos, light_brightness, world);
    }
    return background_color;
}

static unsigned char to_byte(float v) {
    v = std::max(0.0f, std::min(1.0f, v));
    return static_cast<unsigned char>(255.999f * v);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input.txt> <output.ppm>\n";
        return 1;
    }

    std::ifstream in(argv[1]);
    if (!in) {
        std::cerr << "Failed to open input file: " << argv[1] << "\n";
        return 1;
    }

    int image_width;
    int image_height;
    float viewport_height;
    float focal_length;
    Vec3 light_pos;
    float light_brightness;
    int color_count;
    std::vector<unsigned int> colors;
    int background_index;
    int sphere_count;

    in >> image_width >> image_height;
    in >> viewport_height;
    in >> focal_length;
    in >> light_pos.x >> light_pos.y >> light_pos.z >> light_brightness;
        in >> color_count;
    colors.resize(color_count);
    for (int i = 0; i < color_count; ++i) {
        std::string hex;
        in >> hex;
        unsigned int value = 0;
        std::sscanf(hex.c_str(), "0x%06x", &value);
        colors[i] = value;
    }
    in >> background_index;
    in >> sphere_count;

    if (background_index < 0 || background_index >= color_count) {
        std::cerr << "Invalid background color index\n";
        return 1;
    }

    qsort(colors.data(), color_count, sizeof(unsigned int), compareColor);

    std::vector<Vec3> palette(color_count);
    for (int i = 0; i < color_count; ++i) {
        palette[i] = unpackRGB(colors[i]);
    }

    Vec3 background_color = palette[background_index];

    Camera camera(image_width, image_height, viewport_height, focal_length);
    World world;

    std::vector<Sphere> spheres;
    spheres.reserve(sphere_count);
    for (int i = 0; i < sphere_count; ++i) {
        Vec3 center;
        float radius;
        int color_index;
        in >> center.x >> center.y >> center.z >> radius >> color_index;
        if (color_index < 0 || color_index >= color_count) {
            std::cerr << "Invalid sphere color index\n";
            return 1;
        }
        Vec3 sphere_color = palette[color_index];
        spheres.emplace_back(center, radius, sphere_color);
        world.add(&spheres.back());
    }

    std::ofstream out(argv[2], std::ios::binary);
    out << "P6\n" << image_width << ' ' << image_height << "\n255\n";

        const float sample_offsets[3] = {1.0f / 6.0f, 3.0f / 6.0f, 5.0f / 6.0f};

    for (int j = image_height - 1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            Vec3 pixel_color{0.0f, 0.0f, 0.0f};
            for (int sy = 0; sy < 3; ++sy) {
                for (int sx = 0; sx < 3; ++sx) {
                    float u = (i + sample_offsets[sx]) / (image_width - 1);
                    float v = (j + sample_offsets[sy]) / (image_height - 1);
                    Ray r = camera.get_ray(u, v);
                    pixel_color = pixel_color + ray_color(r, world, background_color, light_pos, light_brightness);
                }
            }
            pixel_color = pixel_color / 9.0f;

            unsigned char pixel[3] = {
                to_byte(pixel_color.x),
                to_byte(pixel_color.y),
                to_byte(pixel_color.z)
            };
            out.write(reinterpret_cast<char*>(pixel), 3);
        }
    }
    out.close();

    std::cout << "Rendered " << argv[2] << "\n";
    return 0;
}