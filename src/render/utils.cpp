#include "utils.h"

namespace render {
static render::screen_settings ss = render::get_screen_settings();

void draw_text(const char *text, int x, int y) {
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0, ss.width, 0, ss.height);

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

void draw_text_transparence(const char *text, int x, int y, float transparence) {
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0, ss.width, 0, ss.height);

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  float blanc[]={transparence,transparence,transparence,1.0F};
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,blanc);

  glRasterPos2i(x, y);
  for (const char *c = text; *c; ++c) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
  }

  glPopMatrix();

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();

  glMatrixMode(GL_MODELVIEW);
}

void draw_title(const char *text, int x, int y) {
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0, ss.width, 0, ss.height);

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

void draw_important_text(const char *text) {
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0, ss.width, 0, ss.height);

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  float blanc[]={1.0F,1.0F,1.0F,1.0F};
  float noir[]={0.0F,0.0F,0.0F,1.0F};
  glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,blanc);
  float text_width=0.0F;
  
  for (const char *c = text; *c; ++c) {
    text_width += glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24, *c);
  }
  

  glRasterPos2i(ss.width/2-text_width/2, ss.height/2-8);
  for (const char *c = text; *c; ++c) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
  }
  
  float xMax =ss.width/2+text_width/2+4;
  float xMin =ss.width/2-text_width/2-4;
  float yMax =ss.height/2+12;
  float yMin =ss.height/2-12;
  
  
  glMaterialfv(GL_FRONT,GL_EMISSION,noir);
  glMaterialfv(GL_FRONT,GL_DIFFUSE,noir);
  glBegin(GL_QUADS);
  glVertex3f(xMin, yMin, -0.5F);
  glVertex3f(xMax, yMin, -0.5F);
  glVertex3f(xMax, yMax, -0.5F);
  glVertex3f(xMin, yMax, -0.5F);
  glEnd();

  glPopMatrix();

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();

  glMatrixMode(GL_MODELVIEW);
}

void draw_text_3d(float x, float y, float z, const char *text) {
  glRasterPos3f(x, y, z);
  while (*text) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *text++);
  }
}

} // namespace render
