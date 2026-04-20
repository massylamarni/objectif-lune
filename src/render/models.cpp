#include "models.h"
#include "../../assets/models/color_palette.h"
#include "../world/planet.h"
#include "../world/world.h"
#include <GL/gl.h>
#include <algorithm>
#include <cmath>

namespace render {
constexpr int MOON_TERRAIN_SIZE = 250;
constexpr float MOON_TERRAIN_SCALE = 5.0f;
constexpr float MOON_LOD_DISTANCE = 300.0f;
constexpr float TERRAIN_FADE_START = 300.0f;
constexpr float TERRAIN_FADE_END = 200.0f;
constexpr float MOON_HEIGHT_BIAS = 10.0f;



Vec3 lerp(const Vec3 &a, const Vec3 &b, float u) {
  return a * (1.0f - u) + b * u;
}

float moon_height(float x, float z) {
  return std::sin(x * 0.05f) * std::cos(z * 0.05f) * MOON_HEIGHT_BIAS;
}

void moon_height_grad(float x, float z, float *dx, float *dz) {
  *dx = 0.05f * std::cos(x * 0.05f) * std::cos(z * 0.05f) * MOON_HEIGHT_BIAS;
  *dz = -0.05f * std::sin(x * 0.05f) * std::sin(z * 0.05f) * MOON_HEIGHT_BIAS;
}

void draw_moon_sphere(const world::Planet &planet) {
  const uint *texture_id_buf = get_texture_id_buf();
  glPushMatrix();
  glTranslatef(planet.position.x, planet.position.y, planet.position.z);
  material_white();
  // glBindTexture(GL_TEXTURE_2D, texture_id_buf[MOON_TEXTURE]);
  GLUquadric *quad = gluNewQuadric();
  gluQuadricTexture(quad, GL_TRUE);
  gluQuadricNormals(quad, GLU_SMOOTH);
  gluSphere(quad, planet.radius, 64, 64);
  gluDeleteQuadric(quad);
  glPopMatrix();
}

void build_moon_tangent_frame(const Vec3 &surface_normal, Vec3 *e1, Vec3 *e2) {
  const Vec3 ref = (std::fabs(surface_normal.y) < 0.9f)
                       ? Vec3(0.0f, 1.0f, 0.0f)
                       : Vec3(1.0f, 0.0f, 0.0f);
  *e1 = normalize(cross(ref, surface_normal));
  if (length(*e1) < 1e-5f) {
    *e1 = Vec3(1.0f, 0.0f, 0.0f);
  } else {
    *e1 = normalize(*e1);
  }
  *e2 = normalize(cross(surface_normal, *e1));
}

void draw_moon_terrain(const world::Planet &moon, const Vec3 &ship_position,
                       float t) {
  Vec3 to_ship = ship_position - moon.position;
  float r = length(to_ship);
  Vec3 normal = (r > 1e-5f) ? to_ship / r : Vec3(1.0f, 0.0f, 0.0f);

  Vec3 e1, e2;
  build_moon_tangent_frame(normal, &e1, &e2);

  const Vec3 terrain_center = moon.position + normal * moon.radius;

  const int SIZE = MOON_TERRAIN_SIZE;
  const float SCALE = MOON_TERRAIN_SCALE;
  const uint *texture_id_buf = get_texture_id_buf();

  glPushMatrix();
  glTranslatef(moon.position.x, moon.position.y, moon.position.z);

  material_white();
  // glBindTexture(GL_TEXTURE_2D, texture_id_buf[MOON_TEXTURE]);

  for (int z = 0; z < SIZE - 1; z++) {
    glBegin(GL_TRIANGLE_STRIP);
    for (int x = 0; x < SIZE; x++) {
      const float x0 =
          (static_cast<float>(x) - static_cast<float>(SIZE) / 2.0f) * SCALE;
      const float z_row0 =
          (static_cast<float>(z) - static_cast<float>(SIZE) / 2.0f) * SCALE;
      const float z_row1 =
          (static_cast<float>(z + 1) - static_cast<float>(SIZE) / 2.0f) * SCALE;

      for (int pass = 0; pass < 2; pass++) {
        const float zc = (pass == 0) ? z_row0 : z_row1;
        float u = 1.0f - t;
        u = u * u * (3.0f - 2.0f * u);
        const float h = MOON_HEIGHT_BIAS + moon_height(x0, zc) * u;
        float hdx, hdz;
        moon_height_grad(x0, zc, &hdx, &hdz);
        hdx *= u;
        hdz *= u;
        Vec3 dir = normalize(normal + e1 * (x0 / moon.radius) +
                             e2 * (zc / moon.radius));
        Vec3 base_normal = dir;
        Vec3 detailed = normalize(e1 * (-hdx) + base_normal + e2 * (-hdz));
        Vec3 n_world = normalize(lerp(base_normal, detailed, u));
        glNormal3f(n_world.x, n_world.y, n_world.z);
        glTexCoord2f(x0 * 0.01f, zc * 0.01f);

        Vec3 world_pos = dir * (moon.radius + h);
        glVertex3f(world_pos.x, world_pos.y, world_pos.z);
      }
    }
    glEnd();
  }

  glPopMatrix();
}

float anim_reactor_offset [] = { 0.0F, 10.0F, 20.0F, 30.0F, 40.0F, 50.0F, 60.0F, 70.0F, 80.0F, 90.0F };

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

  glTranslatef(ship.position.x, ship.position.y - 3.0F, ship.position.z);
  explosion_model();

  glPopMatrix();
}
} // namespace render
