#ifndef RAYTRACER_VEC3_HPP
#define RAYTRACER_VEC3_HPP

struct Vec3 {
    float x, y, z;
};

Vec3 operator+(const Vec3 &a, const Vec3 &b);
Vec3 operator-(const Vec3 &a, const Vec3 &b);
Vec3 operator*(const Vec3 &v, float scalar);
Vec3 operator*(float scalar, const Vec3 &v);
Vec3 operator/(const Vec3 &v, float scalar);

float dot(const Vec3 &a, const Vec3 &b);
float length2(const Vec3 &v);
float length(const Vec3 &v);
float distance2(const Vec3 &a, const Vec3 &b);
float distance(const Vec3 &a, const Vec3 &b);
Vec3 normalize(const Vec3 &v);

#endif // RAYTRACER_VEC3_HPP