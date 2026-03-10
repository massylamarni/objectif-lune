#ifndef VEC2
#define VEC2

#include <cmath>

struct Vec2 {
  float x;
  float y;

  Vec2() : x(0), y(0) {}
  Vec2(float x_, float y_) : x(x_), y(y_) {}
};

inline Vec2 operator+(const Vec2 &a, const Vec2 &b) {
  return Vec2(a.x + b.x, a.y + b.y);
}

inline Vec2 operator-(const Vec2 &a, const Vec2 &b) {
  return Vec2(a.x - b.x, a.y - b.y);
}

inline Vec2 operator*(const Vec2 &v, float s) { return Vec2(v.x * s, v.y * s); }

inline Vec2 operator/(const Vec2 &v, float s) { return Vec2(v.x / s, v.y / s); }

inline float length(const Vec2 &v) { return std::sqrt(v.x * v.x + v.y * v.y); }

inline Vec2 normalize(const Vec2 &v) {
  float l = length(v);
  if (l == 0)
    return Vec2();
  return v / l;
}

inline float dot(const Vec2 &a, const Vec2 &b) { return a.x * b.x + a.y * b.y; }

#endif