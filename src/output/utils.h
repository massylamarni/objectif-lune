#include <stdio.h>
#include <stdlib.h>
#include "../math/vec3.h"

namespace output {
char *itos(int val, char* buf);
char *ftos(float f, char* buf, int precision);
char *vec3tos(Vec3 v, char* buf);
} // namespace output
