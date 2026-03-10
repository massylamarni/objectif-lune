#ifndef VEC3
#define VEC3

#include <cmath>

struct Vec3 {
  float x;
  float y;
  float z;

  Vec3() : x(0), y(0), z(0) {}
  Vec3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
};

inline Vec3 operator+(const Vec3 &a, const Vec3 &b) {
  return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline Vec3 operator-(const Vec3 &a, const Vec3 &b) {
  return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

inline Vec3 operator*(const Vec3 &v, float s) {
  return Vec3(v.x * s, v.y * s, v.z * s);
}

inline Vec3 operator/(const Vec3 &v, float s) {
  return Vec3(v.x / s, v.y / s, v.z / s);
}

inline Vec3 &operator+=(Vec3 &a, const Vec3 &b) {
  a.x += b.x;
  a.y += b.y;
  a.z += b.z;
  return a;
}

inline Vec3 &operator-=(Vec3 &a, const Vec3 &b) {
  a.x -= b.x;
  a.y -= b.y;
  a.z -= b.z;
  return a;
}

inline float length(const Vec3 &v) {
  return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

inline Vec3 normalize(const Vec3 &v) {
  float l = length(v);
  if (l == 0)
    return Vec3();
  return v / l;
}

inline float dot(const Vec3 &a, const Vec3 &b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline Vec3 cross(const Vec3 &a, const Vec3 &b) {
  return Vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
              a.x * b.y - a.y * b.x);
}

#endif