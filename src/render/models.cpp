#include "models.h"
#include "../world/world.h"
#include "../../assets/models/color_palette.h"
#include <cmath>

namespace render {

void draw_planet(const world::Planet &planet, Vec3 *ship_position) {
  glPushMatrix();

  glTranslatef(planet.position.x, planet.position.y, planet.position.z);
  
  if (planet.id == MOON_ID) {
    draw_moon_container(planet, ship_position);
  } else {
    material_sun();
    draw_planet_sphere(planet.radius);
  }

  glPopMatrix();
}

void draw_ship(const world::Ship &ship) {
  float anim_reactor_offset [] = { 0.0F, 10.0F, 20.0F, 30.0F, 40.0F, 50.0F, 60.0F, 70.0F, 80.0F, 90.0F };

  glPushMatrix();

  glTranslatef(ship.position.x, ship.position.y, ship.position.z);
  const float RAD2DEG = 180.0f / M_PI;
  glRotatef(ship.rotation.x * RAD2DEG, 1.0f, 0.0f, 0.0f);
  glRotatef(ship.rotation.y * RAD2DEG, 0.0f, 1.0f, 0.0f);
  glRotatef(ship.rotation.z * RAD2DEG, 0.0f, 0.0f, 1.0f);

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
