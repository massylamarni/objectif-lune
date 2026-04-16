#include "models.h"
#include "../../assets/models/color_palette.h"
#include "../world/planet.h"
#include <GL/gl.h>
#include <algorithm>
#include <cmath>
#include "moon_model.h"

namespace render {

void draw_moon(const world::Planet &moon, const Vec3 &ship_position) {
  float dist = world::distance_to_surface(moon, ship_position);

  float t = (dist - TERRAIN_FADE_END) / (TERRAIN_FADE_START - TERRAIN_FADE_END);
  t = std::clamp(t, 0.0f, 1.0f);

  draw_moon_sphere(moon);
  draw_moon_terrain(moon, ship_position, t);
}

void draw_planet(const world::Planet &planet) {
  glPushMatrix();

  glTranslatef(planet.position.x, planet.position.y, planet.position.z);
  material_sun();
  GLUquadric *quad = gluNewQuadric();
  gluQuadricTexture(quad, GL_TRUE);
  gluQuadricNormals(quad, GLU_SMOOTH);
  gluSphere(quad, planet.radius, 64, 64);
  gluDeleteQuadric(quad);

  glPopMatrix();
}

void draw_ship(const world::Ship &ship) {
  glPushMatrix();

  glTranslatef(ship.position.x, ship.position.y, ship.position.z);
  glutSolidCube(1);

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

  glTranslatef(ship.position.x, ship.position.y - 3.0F, ship.position.z);
  explosion_model();

  glPopMatrix();
}
} // namespace render
