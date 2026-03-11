#include "renderer.h"
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>

namespace render {
static float alpha_x = 0.0F;
static float alpha_y = 0.0F;
static float alpha_z = 0.0F;

static bool gl_line_toggle = false;
static bool gl_depth_test_toggle = true;
static bool gl_lighting_toggle = true;
static int prev_x = 0;
static int prev_y = 0;
static int poly_count_step = 1;
static int poly_count_x = 72;
static int poly_count_y = 180;

void init(int *argc, char **argv) {
  atexit(clean);
  glutInit(argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
  glutInitWindowSize(render::SCREEN_WIDTH, render::SCREEN_HEIGHT);
  glutInitWindowPosition(render::SCREEN_POSITION_X, render::SCREEN_POSITION_Y);
  glutCreateWindow("Gestion événementielle de GLUt");

  gl_lighting_toggle ? glEnable(GL_LIGHTING) : glDisable(GL_LIGHTING);
  gl_depth_test_toggle ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
  glEnable(GL_LIGHT0);
  glDepthFunc(GL_LESS);
  glEnable(GL_NORMALIZE);
  // glEnable(GL_CULL_FACE);
  // glCullFace(GL_BACK);
  glClearColor(0.02f, 0.02f, 0.05f, 1.0f);
  // glEnable(GL_COLOR_MATERIAL);

  glutReshapeFunc(reshape);
  // glutMainLoop();
}

static void set_perspective() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  const float NATURAL_PERSPECTIVE = 60.0f;
  gluPerspective(NATURAL_PERSPECTIVE,
                 (double)render::SCREEN_WIDTH / (double)render::SCREEN_HEIGHT,
                 0.1, 1000000.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

static void display_start_frame() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPolygonMode(GL_FRONT_AND_BACK, gl_line_toggle ? GL_LINE : GL_FILL);
}

static void display_end_frame() {
  glFlush();
  glutSwapBuffers();
  int error = glGetError();
  if (error != GL_NO_ERROR)
    printf("Attention erreur %d\n", error);
}

void display(void display_hook(void)) {
  display_start_frame();
  glPushMatrix();

  display_hook();

  glPopMatrix();
  display_end_frame();
}

void idle(void render_hook(void)) {
  render_hook();
  glutPostRedisplay();
}

static void clean(void) {
  // printf("Bye\n");
}

static void reshape(int wx, int wy) {
  // printf("R\n");
  render::SCREEN_HEIGHT = wx;
  render::SCREEN_WIDTH = wy;
  glViewport(0, 0, wx, wy);
  set_perspective();
}
} // namespace render

