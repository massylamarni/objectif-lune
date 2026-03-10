#include "game.h"

static GameState gst;

void game_init(int width, int height) {
  gst.earth = world::create_planet(EARTH_POSITION, EARTH_RADIUS, EARTH_GRAVITY);
  gst.moon = world::create_planet(MOON_POSITION, MOON_RADIUS, MOON_GRAVITY);
  gst.ship = world::create_ship(SHIP_POSITION);
  gst.camera.position = CAMERA_POSITION;
  gst.camera.target = CAMERA_TARGET;
  gst.camera.up = CAMERA_UP;

  game_display();
  game_update();
}

void game_update() {
  glutIdleFunc(game_update_callback);
}

void game_update_callback() {
  core::time_update();
  static float dt = core::time_delta();
  static logs::Logger logger = logs::init();

  physics::RigidBody body;

  body.position = gst.ship.position;
  body.velocity = gst.ship.velocity;
  body.mass = gst.ship.mass;

  physics::apply_planet_gravity(body, gst.earth);
  physics::apply_planet_gravity(body, gst.moon);

  physics::rb_integrate(body, dt);

  gst.ship.position = body.position;
  gst.ship.velocity = body.velocity;

  if (physics::check_planet_collision(body, gst.earth)) {
    physics::resolve_planet_collision(body, gst.earth);
  }

  world::ship_update(gst.ship, dt);

  render::camera_follow_ship(gst.camera, gst.ship);
}

void game_display() {
  glutDisplayFunc(game_display_callback);
}


void game_display_callback() {
  render::display(game_render_hook);
}

void game_render_hook() {
  render::camera_apply(gst.camera);

  render::draw_planet(gst.earth);
  render::draw_planet(gst.moon);

  render::draw_ship(gst.ship);

  
  char buf[128];
  snprintf(buf, sizeof(buf), "cam (%.1f, %.1f, %.1f)",
           gst.camera.position.x, gst.camera.position.y, gst.camera.position.z);
  const int margin = 30;
  int textWidth = 200;
  render::draw_text(buf, render::SCREEN_WIDTH - textWidth - margin, render::SCREEN_HEIGHT - margin);
}