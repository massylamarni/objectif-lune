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
