#include "renderer.h"
#include "renderer_settings.h"
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>

namespace render {
static render_settings rs = {0};

void init(int *argc, char **argv) {
  atexit(clean);
  glutInit(argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
  glutInitWindowSize(render::SCREEN_WIDTH, render::SCREEN_HEIGHT);
  glutInitWindowPosition(render::SCREEN_POSITION_X, render::SCREEN_POSITION_Y);
  glutCreateWindow("Gestion événementielle de GLUt");

  glDepthFunc(GL_LESS);
  glEnable(GL_NORMALIZE);
  // glEnable(GL_CULL_FACE);
  // glCullFace(GL_BACK);
  glClearColor(0.02f, 0.02f, 0.05f, 1.0f);
  // glEnable(GL_COLOR_MATERIAL);

  glutReshapeFunc(reshape);
  // glutMainLoop();
}

static void set_lighting() {
  float white[] =     { 1.0F, 1.0F, 1.0F, 1.0F };

  glEnable(GL_LIGHT0);
  glLightfv (GL_LIGHT0, GL_DIFFUSE,  white);
  glLightfv (GL_LIGHT0, GL_SPECULAR, white);
  glLightfv (GL_LIGHT0, GL_AMBIENT,  white);
  glLightfv (GL_LIGHT0, GL_AMBIENT,  white);
}

static void set_material() {
  glColorMaterial (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}

static void set_perspective() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  const float NATURAL_PERSPECTIVE = 60.0f;
  gluPerspective(NATURAL_PERSPECTIVE,
                 (double)render::SCREEN_HEIGHT / (double)render::SCREEN_WIDTH,
                 0.1, 1000000.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

static void display_start_frame() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

