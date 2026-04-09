#include "models.h"

namespace render {
void draw_planet(const world::Planet &planet) {
  glPushMatrix();

  glTranslatef(planet.position.x, planet.position.y, planet.position.z);
  glutSolidSphere(planet.radius, 32, 32);

  glPopMatrix();
}

void draw_ship(const world::Ship &ship) {
  glPushMatrix();

  glTranslatef(ship.position.x, ship.position.y, ship.position.z);
  // glutSolidCube(1);
  rectangle(7.5F, 5.0F);

  glPopMatrix();
}

void draw_lem() {
  glPushMatrix();

  glTranslatef(-2.0F, -1.0F, 0.0F);

  glPopMatrix();
}

void draw_explosion() {
  glPushMatrix();

  glTranslatef(0.0F, -1.0F, 0.0F);

  glPopMatrix();
}

void rectangle(float largeur, float hauteur) {
  largeur /= 2.0F;
  hauteur /= 2.0F;
  float profondeur = 1.0F;
  const uint *texture_id_buf = get_texture_id_buf();
  const uint texture_id_buf_len = get_texture_id_buf_len();

  glPushMatrix();

  glBindTexture(GL_TEXTURE_2D, texture_id_buf[0]);
  glBegin(GL_QUADS);
  glNormal3f(0.0F, 0.0F, 1.0F);
  glTexCoord2f(0.0F, 0.0F); glVertex3f(-largeur, -hauteur, profondeur);
  glTexCoord2f(1.0F, 0.0F); glVertex3f(largeur, -hauteur, profondeur);
  glTexCoord2f(1.0F, 1.0F); glVertex3f(largeur, hauteur, profondeur);
  glTexCoord2f(0.0F, 1.0F); glVertex3f(-largeur, hauteur, profondeur);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, texture_id_buf[1]);
  glBegin(GL_QUADS);
  glNormal3f(0.0F, 0.0F, -1.0F);
  glTexCoord2f(0.0F, 0.0F); glVertex3f(largeur, -hauteur, -profondeur);
  glTexCoord2f(1.0F, 0.0F); glVertex3f(-largeur, -hauteur, -profondeur);
  glTexCoord2f(1.0F, 1.0F); glVertex3f(-largeur, hauteur, -profondeur);
  glTexCoord2f(0.0F, 1.0F); glVertex3f(largeur, hauteur, -profondeur);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, texture_id_buf[2]);
  glBegin(GL_QUADS);
  glNormal3f(-1.0F, 0.0F, 0.0F);
  glTexCoord2f(0.0F, 0.0F); glVertex3f(-largeur, -hauteur, -profondeur);
  glTexCoord2f(1.0F, 0.0F); glVertex3f(-largeur, -hauteur, profondeur);
  glTexCoord2f(1.0F, 1.0F); glVertex3f(-largeur, hauteur, profondeur);
  glTexCoord2f(0.0F, 1.0F); glVertex3f(-largeur, hauteur, -profondeur);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, texture_id_buf[3]);
  glBegin(GL_QUADS);
  glNormal3f(1.0F, 0.0F, 0.0F);
  glTexCoord2f(0.0F, 0.0F); glVertex3f(largeur, -hauteur, profondeur);
  glTexCoord2f(1.0F, 0.0F); glVertex3f(largeur, -hauteur, -profondeur);
  glTexCoord2f(1.0F, 1.0F); glVertex3f(largeur, hauteur, -profondeur);
  glTexCoord2f(0.0F, 1.0F); glVertex3f(largeur, hauteur, profondeur);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, texture_id_buf[4]);
  glBegin(GL_QUADS);
  glNormal3f(0.0F, 1.0F, 0.0F);
  glTexCoord2f(0.0F, 0.0F); glVertex3f(-largeur, hauteur, profondeur);
  glTexCoord2f(1.0F, 0.0F); glVertex3f(largeur, hauteur, profondeur);
  glTexCoord2f(1.0F, 1.0F); glVertex3f(largeur, hauteur, -profondeur);
  glTexCoord2f(0.0F, 1.0F); glVertex3f(-largeur, hauteur, -profondeur);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, texture_id_buf[5]);
  glBegin(GL_QUADS);
  glNormal3f(0.0F, -1.0F, 0.0F);
  glTexCoord2f(0.0F, 0.0F); glVertex3f(-largeur, -hauteur, -profondeur);
  glTexCoord2f(1.0F, 0.0F); glVertex3f(largeur, -hauteur, -profondeur);
  glTexCoord2f(1.0F, 1.0F); glVertex3f(largeur, -hauteur, profondeur);
  glTexCoord2f(0.0F, 1.0F); glVertex3f(-largeur, -hauteur, profondeur);
  glEnd();

  glPopMatrix();
}
} // namespace render