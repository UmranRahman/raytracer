#include <cassert>
#include <cmath>
#include "../src/vec3.hpp"

static bool approxEqual(float a, float b, float eps = 1e-5f){
    return std::fabs(a-b) < eps;
}

static bool approxEqual(const Vec3 &a, const Vec3 &b, float eps = 1e-5f) {
    return approxEqual(a.x, b.x, eps) && approxEqual(a.y, b.y, eps) && approxEqual(a.z, b.z, eps);
}

int main() {
    Vec3 origin{0.0f, 0.0f, 0.0f};
    Vec3 lightPos{20.0f, 20.0f, 10.0f};

    // Vector addition and subtraction
    assert(approxEqual(origin + lightPos, lightPos));
    assert(approxEqual(origin - lightPos, Vec3{-20.0f, -20.0f, -10.0f}));

    // Scalar multiplication and division
    Vec3 scaled = lightPos * 2.7f;
    assert(approxEqual(scaled, Vec3{54.0f, 54.0f, 27.0f}, 1e-3f));

    Vec3 white{1.0f, 1.0f, 1.0f};
    assert(approxEqual(white / 2.0f, Vec3{0.5f, 0.5f, 0.5f}));

    assert(approxEqual(dot(lightPos, Vec3{2.0f, 0.0f, -5.0f}), -10.0f));
    assert(approxEqual(distance(lightPos, Vec3{2.0f, 0.0f, -5.0f}), 30.806f, 1e-3f));
    assert(approxEqual(length(Vec3{2.0f, 0.0f, -5.0f}), 5.385f, 1e-3f));

    // Normalize
    Vec3 norm = normalize(lightPos);
    assert(approxEqual(length(norm), 1.0f));

    return 0;
}