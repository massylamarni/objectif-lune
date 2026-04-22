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
  float blanc[]={1.0F,1.0F,1.0F,1.0F};
  float noir[]={0.0F,0.0F,0.0F,1.0F};
  float text_width=0.0F;
  float text_height=18.0F;
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,blanc);

  glRasterPos2i(x, y);
  for (const char *c = text; *c; ++c) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    text_width += glutBitmapWidth(GLUT_BITMAP_HELVETICA_18, *c);
  }
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,noir);
  glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,noir);
  glBegin(GL_QUADS);
  glVertex3f(x, y-1.0F, -0.5F);
  glVertex3f(x+text_width, y-1.0F, -0.5F);
  glVertex3f(x+text_width, y+text_height, -0.5F);
  glVertex3f(x, y+text_height, -0.5F);
  glEnd();

  glPopMatrix();

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();

  glMatrixMode(GL_MODELVIEW);
}

void draw_text_pause(const char *text, float x, float y) {
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0, render::SCREEN_WIDTH, 0, render::SCREEN_HEIGHT);

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  float blanc[]={1.0F,1.0F,1.0F,1.0F};
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,blanc);

  glRasterPos2i(x, y);
  for (const char *c = text; *c; ++c) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
  }

  glPopMatrix();

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();

  glMatrixMode(GL_MODELVIEW);
}

} // namespace render
