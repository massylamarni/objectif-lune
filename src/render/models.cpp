#include "models.h"
#include "../../assets/models/color_palette.h"
#include "../world/world.h"
#include "renderer.h"
#include "textures.h"
#include <GL/freeglut_std.h>
#include <cmath>

namespace render {

float animation_counter = 0.0F;

float anim_win_offset = 0.0F;
bool win_value = false;
bool reactor_activity = true;
float rotation_power = 0.0F;
float rotation_direction = 0.0F;

void draw_planet(const world::Planet &planet, Vec3 *ship_position) {
  const uint *texture_id_buf = render::get_texture_id_buf();

  glPushMatrix();
  glTranslatef(planet.position.x, planet.position.y, planet.position.z);

  if (planet.id == MOON_ID) {
    draw_moon_container(planet, ship_position);
  } else if (planet.id == SUN_ID) {
    Vec3 sun_dir = planet.position;
    float len = length(sun_dir);
    if (len > 0)
      sun_dir = sun_dir / len;
    float light_pos[4] = {sun_dir.x, sun_dir.y, sun_dir.z, 0.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    material_sun();
    glBindTexture(GL_TEXTURE_2D, texture_id_buf[render::SUN_TEXTURE]);
    draw_planet_sphere(planet.radius);
  } else {
    glBindTexture(GL_TEXTURE_2D, texture_id_buf[render::EARTH_TEXTURE]);
    draw_planet_sphere(planet.radius);
  }

  glPopMatrix();
}

void draw_mini_planet(const world::Planet &planet, Vec3 *ship_position) {
  const uint *texture_id_buf = render::get_texture_id_buf();

  glPushMatrix();
  glTranslatef(planet.position.x, planet.position.y, planet.position.z);

  if (planet.id == MOON_ID) {
    glBindTexture(GL_TEXTURE_2D, texture_id_buf[render::MOON_TEXTURE]);
    draw_planet_sphere(planet.radius);
  } else if (planet.id == SUN_ID) {
    Vec3 sun_dir = planet.position;
    float len = length(sun_dir);
    if (len > 0)
      sun_dir = sun_dir / len;
    float light_pos[4] = {sun_dir.x, sun_dir.y, sun_dir.z, 0.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    material_sun();
    glBindTexture(GL_TEXTURE_2D, texture_id_buf[render::SUN_TEXTURE]);
    draw_planet_sphere(planet.radius);
  } else {
    glBindTexture(GL_TEXTURE_2D, texture_id_buf[render::EARTH_TEXTURE]);
    draw_planet_sphere(planet.radius);
  }

  glPopMatrix();
}


void draw_skybox(float radius, const Vec3 *ship_position) {
  glPushMatrix();
  material_sun();
  glTranslatef(ship_position->x, ship_position->y, ship_position->z);
  const uint *texture_id_buf = render::get_texture_id_buf();
  glBindTexture(GL_TEXTURE_2D, texture_id_buf[render::SKYBOX_TEXTURE]);
  GLUquadric *quad = gluNewQuadric();
  gluQuadricTexture(quad, GL_TRUE);
  gluQuadricNormals(quad, GLU_SMOOTH);
  gluSphere(quad, radius, 8, 8);
  gluDeleteQuadric(quad);
  glPopMatrix();
}

void idle_ship(float dt, float win_v, bool thrusting, float rotation_power_v) {
  animation_counter += dt * 200;
  win_value = win_v;
  rotation_power = rotation_power_v;
  input::InputState iState = input::get_input_state();
  render::screen_settings &ss = render::get_screen_settings();
  if (iState.rmb_down && !win_value)
    rotation_update(iState.mouse_abs.x + (float)ss.width / 2,
                    iState.mouse_abs.y + (float)ss.height / 2, ss.width, ss.height,
                    &rotation_direction, &rotation_power);
  if (thrusting && !reactor_activity && !win_value) {
    reactor_init(true, animation_counter);
  }
  reactor_activity = thrusting;

  if (reactor_activity && !win_value)
    reactor_idle(true, animation_counter);
  reactor_idle(false, animation_counter);
}

void draw_ship(const world::Ship &ship) {
  init_lem(get_texture_id_buf()[LEM_TEXTURE]);

  glPushMatrix();

  glTranslatef(ship.position.x, ship.position.y, ship.position.z);

  const float RAD2DEG = 180.0f / M_PI;
  glRotatef(-ship.rotation.y * RAD2DEG, 0.0f, 1.0f, 0.0f);
  glRotatef(ship.rotation.x * RAD2DEG, 1.0f, 0.0f, 0.0f);
  // glRotatef(ship.rotation.z * RAD2DEG, 0.0f, 0.0f, 1.0f);

  // glutWireCube(1);
  glScalef(0.28F, 0.28F, 0.28F);
  glTranslatef(0.0F, -1.4F, 0.0F);

  glRotatef(90.0F, 0.0f, 1.0f, 0.0f);
  lem(reactor_activity, 180.0F - rotation_direction, rotation_power,
      anim_win_offset, win_value, animation_counter, 8);
  // (TO CONNECT reactor_activity, TO CONNECT rotation_direction, TO CONNECT
  // rotation_power, anim_win_offset, TO CONNECT anim_reactor_offset, TO CONNECT
  // win_value, KO general_animation, OK)
  glBindTexture(GL_TEXTURE_2D, 0);
  glPopMatrix();
}

void draw_mini_ship(const world::Ship &ship) {
  glPushMatrix();

  glScalef(0.8F, 0.8F, 0.8F);
  // draw_ship(ship);
  lem(reactor_activity, 180.0F - rotation_direction, rotation_power,
      anim_win_offset, win_value, animation_counter, 8);

  glPopMatrix();
}

void draw_explosion(const world::Ship &ship) {
  glPushMatrix();
  glTranslatef(ship.position.x, ship.position.y, ship.position.z);
  float pos_l7[4] = {0.0F, 0.0F, 0.0F, 1.0F};
  float col_l7[4] = {1.0F, 0.0F, 0.0F, 1.0F};
  glLightfv(GL_LIGHT7, GL_POSITION, pos_l7);
  glLightfv(GL_LIGHT7, GL_DIFFUSE, col_l7);
  glEnable(GL_LIGHT7);

  glScalef(2.0f, 2.0f, 2.0f);
  explosion_model();
  if (getExplosionPhase() == 4) {
    glDisable(GL_LIGHT7);
  }

  glPopMatrix();
}
} // namespace render
