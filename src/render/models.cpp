#include "models.h"

namespace render {
void draw_planet(const world::Planet &planet) {
  const uint *texture_id_buf = get_texture_id_buf();
  glPushMatrix();

  glTranslatef(planet.position.x, planet.position.y, planet.position.z);
  glBindTexture(GL_TEXTURE_2D, texture_id_buf[MOON_TEXTURE]);
  GLUquadric *quad = gluNewQuadric();
  gluQuadricTexture(quad, GL_TRUE);
  gluQuadricNormals(quad, GLU_SMOOTH);
  gluSphere(quad, planet.radius, 32, 32);
  gluDeleteQuadric(quad);

  glPopMatrix();
}

void draw_ship(const world::Ship &ship) {
  glPushMatrix();

  glTranslatef(ship.position.x, ship.position.y, ship.position.z);
  glutSolidCube(1);

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
  explosion_model();

  glPopMatrix();
}
} // namespace render
