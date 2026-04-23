#include "noise.h"
#include <cmath>

float hash(int x, int z) {
  int n = x * 374761393 + z * 668265263;
  n = (n ^ (n >> 13)) * 1274126177;
  return 1.0f - ((n ^ (n >> 16)) & 0x7fffffff) / 1073741824.0f;
}

float lerp(float a, float b, float t) { return a + t * (b - a); }

float smoothstep(float t) { return t * t * (3.0f - 2.0f * t); }

float noise(float x, float z) {
  int x0 = (int)floor(x);
  int z0 = (int)floor(z);
  int x1 = x0 + 1;
  int z1 = z0 + 1;

  float sx = smoothstep(x - x0);
  float sz = smoothstep(z - z0);

  float n00 = hash(x0, z0);
  float n10 = hash(x1, z0);
  float n01 = hash(x0, z1);
  float n11 = hash(x1, z1);

  float ix0 = lerp(n00, n10, sx);
  float ix1 = lerp(n01, n11, sx);

  return lerp(ix0, ix1, sz);
}

float fbm(float x, float z) {
  float total = 0.0f;
  float amplitude = 1.0f;
  float frequency = 0.01f;

  for (int i = 0; i < 4; ++i) {
    total += noise(x * frequency, z * frequency) * amplitude;
    amplitude *= 0.5f;
    frequency *= 2.0f;
  }

  return total;
}