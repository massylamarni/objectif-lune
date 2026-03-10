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

  glutKeyboardFunc(keyboard);
  glutSpecialFunc(special);
  glutMouseFunc(mouse);
  glutMotionFunc(mouseMotion);
  // glutPassiveMotionFunc(passiveMouseMotion);
  glutReshapeFunc(reshape);
  glutIdleFunc(idle);
  // glutIdleFunc(NULL);
  // glutDisplayFunc(display);
  // glutMainLoop();
}

static void quad(void) { glutSolidCube(50); }

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

void display(void render_hook(void)) {
  display_start_frame();
  glPushMatrix();

  render_hook();

  glPopMatrix();
  display_end_frame();
}

static void reshape(int wx, int wy) {
  // printf("R\n");
  render::SCREEN_HEIGHT = wx;
  render::SCREEN_WIDTH = wy;
  glViewport(0, 0, wx, wy);
  set_perspective();
}

static void idle(void) { glutPostRedisplay(); }

static void keyboard(unsigned char key, int x, int y) {
  switch (key) {
  case 0x1B:
    exit(0);
    break;
  case ' ':
    gl_line_toggle = !gl_line_toggle;
    glutPostRedisplay();
    break;
  case 0x0D: {
    static int anim = 1;
    anim = !anim;
    glutIdleFunc((anim) ? idle : NULL);
  } break;
  case 'n':
    poly_count_x -= poly_count_step;
    glutPostRedisplay();
    break;
  case 'N':
    poly_count_x += poly_count_step;
    glutPostRedisplay();
    break;
  case 'm':
    poly_count_y -= poly_count_step;
    glutPostRedisplay();
    break;
  case 'M':
    poly_count_y += poly_count_step;
    glutPostRedisplay();
    break;
  case 'd':
    gl_depth_test_toggle = !gl_depth_test_toggle;
    glutPostRedisplay();
    break;
  case 'l':
    gl_lighting_toggle = !gl_lighting_toggle;
    glutPostRedisplay();
    break;
  }
}
static void special(int specialKey, int x, int y) {
  // printf("S  %4d %4d %4d\n",specialKey,x,y);
  switch (specialKey) {
  case GLUT_KEY_LEFT:
    alpha_y++;
    glutPostRedisplay();
    break;
  case GLUT_KEY_RIGHT:
    alpha_y--;
    glutPostRedisplay();
    break;
  case GLUT_KEY_UP:
    alpha_x--;
    glutPostRedisplay();
    break;
  case GLUT_KEY_DOWN:
    alpha_x++;
    glutPostRedisplay();
    break;
  }
}

static void mouse(int button, int state, int x, int y) {
  // printf("M  %4d %4d %4d %4d\n",button,state,x,y);
}

static void mouseMotion(int x, int y) {
  // printf("MM %4d %4d\n",x,y);
  static int threshold = 3;
  static int affinity = 10;
  if (x >= prev_x + threshold) {
    alpha_y += affinity;
  } else if (x < prev_x - threshold) {
    alpha_y -= affinity;
  }
  if (y >= prev_y + threshold) {
    alpha_x += affinity;
  } else if (y < prev_y - threshold) {
    alpha_x -= affinity;
  }
  prev_x = x;
  prev_y = y;
  glutPostRedisplay();
}

static void passiveMouseMotion(int x, int y) {
  // printf("PM %4d %4d\n",x,y);
}

static void clean(void) {
  // printf("Bye\n");
}

void draw_text(const char *text, int x, int y) {
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  glRasterPos2i(x, y);
  for (const char *c = text; *c; ++c) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
  }

  glPopMatrix();

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();

  glMatrixMode(GL_MODELVIEW);
}

} // namespace render