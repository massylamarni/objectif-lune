#include "utils.h"
#include <cstdio>

namespace output {
char *itos(int val, char* buf) {
  char *p = buf;
  int tmp = val;
  if (val < 0) {
    *p++ = '-';
    val = -val;
  }
  char *start = p;
  do {
    *p++ = '0' + val % 10;
    val /= 10;
  } while (val);
  *p-- = '\0';
  while (start < p) {
    char t = *start;
    *start++ = *p;
    *p-- = t;
  }
  return buf;
}

char *ftos(float f, char* buf, int precision) {
  int int_part = (int)f;
  float frac_part = f - int_part;
  char *p = buf;
  p += snprintf(p, sizeof(buf) - (p - buf), "%d.", int_part);
  for (int i = 0; i < precision; ++i) {
    frac_part *= 10;
    int digit = (int)frac_part;
    *p++ = '0' + digit;
    frac_part -= digit;
  }
  *p = '\0';
  return buf;
}

char *vec3tos(Vec3 v, char* buf) {
  snprintf(buf, sizeof(char)*64, "x: %f, y: %f, z: %f", v.x, v.y, v.z);
  return buf;
}
} // namespace output
