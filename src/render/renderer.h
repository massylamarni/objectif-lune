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
static void quad(void);
static void scene(void);
void display(void render_hook(void));
static void reshape(int wx, int wy);
static void idle(void);
static void keyboard(unsigned char key, int x, int y);
static void special(int specialKey, int x, int y);
static void mouse(int button, int state, int x, int y);
static void mouseMotion(int x, int y);
static void passiveMouseMotion(int x, int y);
static void clean(void);
void draw_text(const char *text, int x, int y);
} // namespace render

#endif