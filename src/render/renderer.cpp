#include "renderer.h"
#include "renderer_settings.h"
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "../../assets/models/color_palette.h"

namespace render {
static render_settings rs = {0};

void init_lighting() {
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  // glDisable (GL_LIGHT0);

  glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
  glLightfv(GL_LIGHT0, GL_SPECULAR, white);
  glLightfv(GL_LIGHT0, GL_AMBIENT, white);

  glLightfv(GL_LIGHT1, GL_DIFFUSE, grey);
  glLightfv(GL_LIGHT1, GL_SPECULAR, grey);
  glLightfv(GL_LIGHT1, GL_AMBIENT, grey);

  glLightfv(GL_LIGHT2, GL_DIFFUSE, red_boost);
  glLightfv(GL_LIGHT2, GL_SPECULAR, gold);
  glLightfv(GL_LIGHT2, GL_AMBIENT, white);
  glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.0F);
  glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 1.0F);
  glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 1.0F);

  glLightfv(GL_LIGHT3, GL_DIFFUSE, red_boost);
  glLightfv(GL_LIGHT3, GL_SPECULAR, gold);
  glLightfv(GL_LIGHT3, GL_AMBIENT, white);
  glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 0.0F);
  glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 1.0F);
  glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 1.0F);

  glLightfv(GL_LIGHT4, GL_DIFFUSE, red_boost);
  glLightfv(GL_LIGHT4, GL_SPECULAR, gold);
  glLightfv(GL_LIGHT4, GL_AMBIENT, white);
  glLightf(GL_LIGHT4, GL_CONSTANT_ATTENUATION, 0.0F);
  glLightf(GL_LIGHT4, GL_LINEAR_ATTENUATION, 1.0F);
  glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, 1.0F);
}

void init(int *argc, char **argv) {
  atexit(clean);
  glutInit(argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
  glutInitWindowSize(render::SCREEN_WIDTH, render::SCREEN_HEIGHT);
  glutInitWindowPosition(render::SCREEN_POSITION_X, render::SCREEN_POSITION_Y);
  glutCreateWindow("Gestion événementielle de GLUt");

  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  // glEnable(GL_CULL_FACE);
  // glCullFace(GL_BACK);
  glClearColor(0.02f, 0.02f, 0.05f, 1.0f);
  // glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

  glutReshapeFunc(reshape);
  // glutMainLoop();
  init_lighting();
}

static void set_perspective() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  /*
    double ratio = (double)w/h;
    if (ratio < 1.0) gluPerspective(12.0/ratio, ratio, 90, 110);
    else gluPerspective(12.0, ratio, 90, 110);
  */

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

