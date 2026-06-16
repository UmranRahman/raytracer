#include "vec3.hpp"
#include <cmath>

Vec3 operator + (const Vec3 &a, const Vec3 &b) {
    return Vec3{a.x + b.x, a.y + b.y, a.z + b.z};
}

Vec3 operator - (const Vec3 &a, const Vec3 &b) {
    return Vec3{a.x - b.x, a.y - b.y, a.z - b.z};
}

Vec3 operator * (const Vec3 &v, float scalar) {
    return Vec3{v.x * scalar, v.y * scalar, v.z * scalar};
}

Vec3 operator * (float scalar, const Vec3 &v) {
    return v * scalar;
}

Vec3 operator / (const Vec3 &v, float scalar) {
    return Vec3{v.x / scalar, v.y / scalar, v.z / scalar};
}

float dot(const Vec3 &a, const Vec3 &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float length2(const Vec3 &v) {
    return dot(v, v);
}

float length(const Vec3 &v) {
    return std::sqrt(length2(v));
}

float distance2(const Vec3 &a, const Vec3 &b) {
    return length2(a - b);
}

float distance(const Vec3 &a, const Vec3 &b) {
    return std::sqrt(distance2(a, b));
}

Vec3 normalize(const Vec3 &v) {
    float len = length(v);
    return v / len;
}