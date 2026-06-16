#include <cassert>
#include <cmath>
#include "../src/ray.hpp"

static bool approxEqual(float a, float b, float eps = 1e-5f) {
    return std::fabs(a - b) < eps;
}

static bool approxEqual(const Vec3 &a, const Vec3 &b, float eps = 1e-5f) {
    return approxEqual(a.x, b.x, eps)
        && approxEqual(a.y, b.y, eps)
        && approxEqual(a.z, b.z, eps);
}

int main() {
    Vec3 origin{0.0f, 0.0f, 0.0f};
    Vec3 direction{0.0f, 0.0f, -1.0f};  // pointing into the screen
    
    Ray ray(origin, direction);
    
    // Test at(t) method
    assert(approxEqual(ray.at(0.0f), Vec3{0.0f, 0.0f, 0.0f}));
    assert(approxEqual(ray.at(1.0f), Vec3{0.0f, 0.0f, -1.0f}));
    assert(approxEqual(ray.at(5.0f), Vec3{0.0f, 0.0f, -5.0f}));
    
    return 0;
}