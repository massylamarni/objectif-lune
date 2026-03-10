#include "utils.h"

namespace render {
void draw_text(const char *text, int x, int y) {
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0, render::SCREEN_WIDTH, 0, render::SCREEN_HEIGHT);

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