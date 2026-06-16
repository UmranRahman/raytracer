#include <cassert>
#include <cmath>
#include "../src/world.hpp"
#include "../src/sphere.hpp"
#include "../src/ray.hpp"

int main() {
    World world;
    Sphere sphere1(Vec3{0.0f, 0.0f, -5.0f}, 1.0f);
    Sphere sphere2(Vec3{0.0f, 0.0f, -10.0f}, 1.0f);

    world.add(&sphere1);
    world.add(&sphere2);

    Ray r(Vec3{0.0f, 0.0f, 0.0f}, Vec3{0.0f, 0.0f, -1.0f});
    float t;
    bool hit = world.hit(r, 0.001f, 1000.0f, t);

    assert(hit);
    assert(t > 0.0f);
    assert(t < 5.5f); // should hit sphere1 first

    return 0;
}