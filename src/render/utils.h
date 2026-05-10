#include "renderer.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdbool.h>
#include <stdlib.h>

namespace render {
int measure_title(const char *text);
int measure_text(const char *text);
void draw_text(const char *text, int x, int y);
void draw_text_transparence(const char *text, int x, int y, float transparence);
void draw_title(const char *text, int x, int y);
void draw_important_text(const char *text);
void draw_text_3d(float x, float y, float z, const char *text);
} // namespace render
