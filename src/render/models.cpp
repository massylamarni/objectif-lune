#include "models.h"
#include "../../assets/models/color_palette.h"
#include "../world/world.h"
#include "renderer.h"
#include "textures.h"
#include <cmath>

namespace render {

float animation_counter = 0.0F;

float anim_win_offset = 0.0F;
bool win_value = false;
bool reactor_activity = true;
float rotation_power = 0.0F;
float rotation_direction = 0.0F;

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

void draw_skybox(float radius) {
  const uint *texture_id_buf = render::get_texture_id_buf();
  glBindTexture(GL_TEXTURE_2D, texture_id_buf[render::SKYBOX_TEXTURE]);
  GLUquadric *quad = gluNewQuadric();
  gluQuadricTexture(quad, GL_TRUE);
  gluQuadricNormals(quad, GLU_SMOOTH);
  gluSphere(quad, radius, 8, 8);
  gluDeleteQuadric(quad);
}

void idle_ship(float dt, float win_v, bool thrusting, float rotation_power_v) {
  animation_counter += dt * 200;
  win_value = win_v;
  rotation_power = rotation_power_v;
  input::InputState iState= input::get_input_state();
  render::screen_settings ss = render::get_screen_settings();
  if (iState.rmb_down)
    rotation_update (iState.mouse_abs.x+ss.width/2, iState.mouse_abs.y+ss.height/2, ss.width, ss.height, &rotation_direction, &rotation_power);
  if (thrusting && !reactor_activity) {
    reactor_init(true, animation_counter);
  }
  reactor_activity = thrusting;

  if (reactor_activity)
    reactor_idle(true, animation_counter);
  reactor_idle(false, animation_counter);
}

void draw_ship(const world::Ship &ship) {
  init_lem(get_texture_id_buf()[LEM_TEXTURE]);

  glPushMatrix();

  glTranslatef(ship.position.x, ship.position.y, ship.position.z);
  const float RAD2DEG = 180.0f / M_PI;
  glRotatef(ship.rotation.x * RAD2DEG, 1.0f, 0.0f, 0.0f);
  glRotatef(ship.rotation.y * RAD2DEG, 0.0f, 1.0f, 0.0f);
  glRotatef(ship.rotation.z * RAD2DEG, 0.0f, 0.0f, 1.0f);

  // glutWireCube(1);
  glScalef(0.28F, 0.28F, 0.28F);
  glTranslatef(0.0F, -1.4F, 0.0F);
  /* Transfer to IDLE
  // à l'init -> reactor_init (true, animation); reactor_init (false,
  animation); (Optionnel si le cpt commence bien entre [0.0, 10.0[ )
  // à l'activation du réacteur ventral -> reactor_init (true, animation);
  reactor_activity -> booléen à modifier quand le réacteur ventral s'active ou
  se désactive if (reactor_activity) reactor_idle (true, animation);
  reactor_idle (false, animation);
  rotation_update (x, y, render::SCREEN_WIDTH, render::SCREEN_HEIGHT,
  &rotation_direction, &rotation_power); //
  */
  lem(reactor_activity, rotation_direction, rotation_power, anim_win_offset,
      win_value, animation_counter, 8);
  // (TO CONNECT reactor_activity, TO CONNECT rotation_direction, TO CONNECT
  // rotation_power, anim_win_offset, TO CONNECT anim_reactor_offset, TO CONNECT
  // win_value, KO general_animation, OK)
  glBindTexture(GL_TEXTURE_2D, 0);
  glPopMatrix();
}

void draw_mini_ship(const world::Ship &ship) {
  glPushMatrix();

  glScalef(0.8F, 0.8F, 0.8F);
  draw_ship(ship);

  glPopMatrix();
}

void draw_lem() {
  glPushMatrix();

  glTranslatef(-2.0F, -1.0F, 0.0F);

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
