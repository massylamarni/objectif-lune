#ifndef RENDER_RENDERER
#define RENDER_RENDERER

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <math.h>

namespace render {
static int SCREEN_WIDTH = 500;
static int SCREEN_HEIGHT = 500;
static int SCREEN_POSITION_X = 50;
static int SCREEN_POSITION_Y = 50;

void init(int *argc, char **argv);
static void set_perspective();
static void display_start_frame();
static void display_end_frame();
void display(void display_hook(void));
void idle(void update_hook(void));
static void clean(void);
static void reshape(int wx, int wy);
} // namespace render

#endif