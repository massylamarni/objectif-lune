#include "renderer.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdbool.h>
#include <stdlib.h>

namespace render {
void draw_text(const char *text, int x, int y);
void draw_text_pause(const char *text, float x, float y);
} // namespace render
