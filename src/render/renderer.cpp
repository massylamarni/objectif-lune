#include "renderer.h"
#include "../../assets/models/color_palette.h"
#include "textures.h"
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>

namespace render {
static screen_settings &ss = get_screen_settings();

void init_lighting() {
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
  glLightfv(GL_LIGHT0, GL_SPECULAR, white);
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
}

void init(int *argc, char **argv) {
  atexit(clean);
  glutInit(argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
  glutInitWindowSize(ss.width, ss.height);
  glutInitWindowPosition(ss.pos_x, ss.pos_y);
  glutCreateWindow("Objectif Lune");

  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glEnable(GL_TEXTURE_2D);
  // glEnable(GL_CULL_FACE);
  // glCullFace(GL_BACK);
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  // glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

  glutReshapeFunc(reshape);
  // glutMainLoop();
  init_lighting();
  load_textures();
  reactor_init(false, 0.0F);
}

void apply_perspective(float fov_degrees, float aspect) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(fov_degrees, aspect, 0.1, 20000.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void apply_orthographic(float half_extent) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-half_extent, half_extent, -half_extent, half_extent, 0.1, 20000.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void display_start_frame() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void display_end_frame() {
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

void clean(void) {
  // printf("Bye\n");
  free_textures();
}

void reshape(int wx, int wy) {
  // printf("R\n");
  ss.width = wx;
  ss.height = wy;
  glViewport(0, 0, wx, wy);
  apply_perspective(NATURAL_PERSPECTIVE, (float)ss.width / (float)ss.height);
}
} // namespace render
