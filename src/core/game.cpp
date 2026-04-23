#include "game.h"
#include <cstdio>

static GameState gst;
static GameFps gfps = {0};

void update_fov() {
  const float FOV_CONST = 500.0f;
  const float MIN_FOV = 30.0f;
  const float MAX_FOV = 80.0f;

  float distance = world::distance_to_surface(gst.moon, gst.ship.position);
  float t = distance / (distance + FOV_CONST);

  float fov = MIN_FOV + t * (MAX_FOV - MIN_FOV);
  static float smooth_fov = 60.0f;
  smooth_fov += (fov - smooth_fov) * 0.1f;
  render::set_perspective(smooth_fov);
}

void game_init(int width, int height) {
  gst.earth =
      world::create_planet(EARTH_ID, EARTH_POSITION, EARTH_RADIUS, EARTH_MASS);
  gst.moon =
      world::create_planet(MOON_ID, MOON_POSITION, MOON_RADIUS, MOON_MASS);
  gst.sun = world::create_planet(SUN_ID, SUN_POSITION, SUN_RADIUS, SUN_MASS);
  gst.ship = world::create_ship(SHIP_POSITION);
  gst.camera = render::create_camera(CAMERA_POSITION, CAMERA_TARGET, CAMERA_UP);
  gst.player_won = false;
  gst.pause = false;

  game_display();
  game_update();
  input::input_init();
}

void game_update() { glutIdleFunc(game_update_callback); }

void game_update_callback() { if(!gst.pause) render::idle(game_update_hook); else render::idle(game_update_pause);}

void game_update_hook() {
  core::time_update();
  float dt = core::time_delta();
  const world::ship_state previous_ship_state = gst.ship.state;
  update_fov();

  physics::RigidBody body;

  body.id = RIGID_BODY_ID;
  body.position = gst.ship.position;
  body.velocity = gst.ship.velocity;
  body.mass = gst.ship.mass;
  body.radius = gst.ship.radius;

  physics::apply_planet_gravity(body, gst.earth);
  physics::apply_planet_gravity(body, gst.moon);
  physics::apply_planet_gravity(body, gst.sun);

  physics::rb_integrate(body, dt);

  if (physics::check_surface_collision(body)) {
    physics::resolve_surface_collision(body);
  }

  gst.ship.position = body.position;
  gst.ship.velocity = body.velocity;
  world::ship_update(gst.ship, dt);
  input::input_update(gst.ship.velocity, gst.ship.rotation);
  input::InputState iState= input::get_input_state();
  if (iState.r_down){
    gst.ship = world::create_ship(SHIP_POSITION);
    gst.player_won = false;
  }
  if (iState.pause){
    input::stop_pause();
    gst.pause = !gst.pause;
    input::stop_mouse_input(gst.pause);
  }
  // physics::update_ship_collision_state(gst.ship);
  if (gst.ship.state == world::SHIP_DESTORYED &&
      previous_ship_state != world::SHIP_DESTORYED) {
    start_explosion_animation();
  }

  gst.player_won = (gst.ship.state == world::SHIP_LANDED);
  if (gst.player_won || gst.ship.state == world::SHIP_DESTORYED) {
    explosion_idle(dt);
    return;
  }

  render::camera_follow_ship(gst.camera, gst.ship);
  explosion_idle(dt);

  update_fps_counter(dt);
}

void game_update_pause() {
  core::time_update();
  update_fov();
  input::InputState iState= input::get_input_state();
  if (iState.pause){
    input::stop_pause();
    gst.pause = !gst.pause;
    input::stop_mouse_input(gst.pause);
  }
  render::camera_follow_ship(gst.camera, gst.ship);
  
}

void game_display() { glutDisplayFunc(game_display_callback); }

void game_display_callback() { render::display(game_display_hook); }

void game_display_hook() {
  render::camera_apply(gst.camera);

  // Sun
  Vec3 sun_dir = gst.sun.position;
  float len = length(sun_dir);
  if (len > 0)
    sun_dir = sun_dir / len;
  float light_pos[4] = {sun_dir.x, sun_dir.y, sun_dir.z, 0.0f};
  glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

  render::draw_planet(gst.earth);
  render::draw_planet(gst.moon, &gst.ship.position);
  render::draw_planet(gst.sun);

  if (gst.ship.state != world::SHIP_DESTORYED) {
    render::draw_ship(gst.ship);
  }
  if (gst.ship.state == world::SHIP_DESTORYED && getExplosionPhase() != 0) {
    render::draw_explosion(gst.ship);
  }
  if (gst.ship.state == world::SHIP_LANDED) {
    render::draw_text("Landing successful - You win!", 20,
                      render::SCREEN_HEIGHT - 70);
    render::draw_text("Press r to Restart", 20,
                      render::SCREEN_HEIGHT - 90);
  } else if (gst.ship.state == world::SHIP_DESTORYED) {
    render::draw_text("Crash detected - Ship destroyed!", 20,
                      render::SCREEN_HEIGHT - 70);
    render::draw_text("Press r to Restart", 20,
                      render::SCREEN_HEIGHT - 90);
  }
  if (gst.pause) {
    render::draw_text_pause("PAUSE", render::SCREEN_WIDTH/2-110.0F,
                      render::SCREEN_HEIGHT/2.0F);
  }

  ui::draw_minimaps(gst.ship, gst.earth, gst.moon, gst.sun, gst.camera);
  output::debug_camera(gst.camera.position.x, gst.camera.position.y,
                       gst.camera.position.z);
  output::debug_fps(gfps.fps);
  draw_moon_transition_overlay();
}

void update_fps_counter(float dt) {
  gfps.frame_count++;
  gfps.fps_time_accumulator += dt;
  if (gfps.fps_time_accumulator >= 0.5f) {
    gfps.fps = gfps.frame_count / gfps.fps_time_accumulator;
    gfps.frame_count = 0;
    gfps.fps_time_accumulator = 0.0f;
  }
}
