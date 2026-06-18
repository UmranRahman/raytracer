#include <cassert>
#include <cmath>
#include "../src/sphere.hpp"
#include "../src/ray.hpp"

static bool approxEqual(float a, float b, float eps = 1e-5f) {
    return std::fabs(a - b) < eps;
}

// optionally add Vec3 approxEqual if needed

int main() {
    Sphere sphere(Vec3{0.0f, 0.0f, -5.0f}, 1.0f);

    Ray ray(Vec3{0.0f, 0.0f, 0.0f}, Vec3{0.0f, 0.0f, -1.0f});
    float t;
    bool hit = sphere.hit(ray, 0.001f, 1000.0f, t);

    assert(hit);
    assert(approxEqual(t, 4.0f)); // or just assert(t > 0.0f)

    Ray missRay(Vec3{0.0f, 0.0f, 0.0f}, Vec3{0.0f, 1.0f, 0.0f});
    assert(!sphere.hit(missRay, 0.001f, 1000.0f, t));

    return 0;
}