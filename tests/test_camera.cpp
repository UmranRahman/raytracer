#include <cassert>
#include <cmath>
#include "../src/camera.hpp"

static bool approxEqual(float a, float b, float eps = 1e-5f) {
    return std::fabs(a - b) < eps;
}

static bool approxEqual(const Vec3 &a, const Vec3 &b, float eps = 1e-5f) {
    return approxEqual(a.x, b.x, eps)
        && approxEqual(a.y, b.y, eps)
        && approxEqual(a.z, b.z, eps);
}

int main() {
    Camera cam(200, 100, 2.0f, 1.0f);

    Ray r = cam.get_ray(0.5f, 0.5f);

    assert(approxEqual(r.origin, Vec3{0.0f, 0.0f, 0.0f}));
    assert(r.direction.z < 0.0f);

    return 0;
}