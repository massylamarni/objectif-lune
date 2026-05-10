#ifndef RENDER_RENDERER
#define RENDER_RENDERER

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "renderer_settings.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "../../assets/models/lem.h"
#include <math.h>

namespace render {
void init(int *argc, char **argv);
void apply_perspective(float fov_degrees, float aspect);
void apply_orthographic(float half_extent);
void apply_orthographic(float half_w, float half_h);
void display_start_frame();
void display_end_frame();
void display(void display_hook(void));
void idle(void update_hook(void));
void clean(void);
void reshape(int wx, int wy);
} // namespace render

#endif
