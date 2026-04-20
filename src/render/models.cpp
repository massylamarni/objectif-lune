#include "models.h"
#include "../world/world.h"
#include "../../assets/models/color_palette.h"

namespace render {
void draw_planet(const world::Planet &planet) {
  const uint *texture_id_buf = get_texture_id_buf();
  glPushMatrix();

  glTranslatef(planet.position.x, planet.position.y, planet.position.z);
  
  if (planet.id == MOON_ID) {
    material_white();
    glBindTexture(GL_TEXTURE_2D, texture_id_buf[MOON_TEXTURE]);
  } else {
    material_sun();
  }
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
  glutWireCube(1);
  init_lem (2); // TODO find the texture index after loading the LEM texture
  glScalef (0.28F, 0.28F, 0.28F);
  glTranslatef(0.0F, -1.4F, 0.0F);
  lem (true, 0.0F, 0.0F, 0.0F, anim_reactor_offset, false, 0.0F, 16);
  glBindTexture(GL_TEXTURE_2D, 0);
  glPopMatrix();
}

void draw_mini_ship(const world::Ship &ship) {
  glPushMatrix();

  glutSolidCube(1);

  glPopMatrix();
}

void draw_lem() {
  glPushMatrix();

  glTranslatef(-2.0F, -1.0F, 0.0F);

  glPopMatrix();
}

void draw_explosion(const world::Ship &ship) {
  glPushMatrix();

  glTranslatef(ship.position.x, ship.position.y-3.0F, ship.position.z);
  explosion_model();

  glPopMatrix();
}
} // namespace render
