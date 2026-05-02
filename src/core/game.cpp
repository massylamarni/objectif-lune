#include "game.h"
#include <cstdio>

static GameState gst;
static GameFps gfps = {0};
static render::screen_settings ss = render::get_screen_settings();

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

void game_init() {
  gst.earth =
      world::create_planet(EARTH_ID, EARTH_POSITION, EARTH_RADIUS, EARTH_MASS);
  gst.moon =
      world::create_planet(MOON_ID, MOON_POSITION, MOON_RADIUS, MOON_MASS);
  gst.sun = world::create_planet(SUN_ID, SUN_POSITION, SUN_RADIUS, SUN_MASS);
  gst.ship = world::create_ship(SHIP_POSITION);
  gst.camera = render::create_camera(CAMERA_POSITION, CAMERA_TARGET, CAMERA_UP);
  gst.player_won = false;
  gst.pause = false;
  gst.debug = false;
  gst.editor = false;

  game_display();
  game_update();
  input::input_init();
  input::simulate_camera_swipe(-200.0f, Vec2(1.0f, 0));
}

void game_update() { glutIdleFunc(game_update_callback); }

void game_update_callback() { 
  if(!gst.pause && !gst.editor) { render::idle(game_update_hook);  }
  else if (!gst.editor) { render::idle(game_update_pause);  }
  else { render::idle(game_update_editor); }
}

void game_update_hook() {
  core::time_update();
  float dt = core::time_delta();
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
  input::input_update(gst.ship, dt);
  input::InputState iState= input::get_input_state();
  if (iState.r_down){
    gst.ship = world::create_ship(SHIP_POSITION);
    gst.player_won = false;
    update_moon_transition(1000.0f, &gst.ship.position);
    glDisable(GL_LIGHT7);
    reset_explosion();
  }
  if (iState.pause){
    input::stop_pause();
    gst.pause = !gst.pause;
    input::stop_mouse_input(gst.pause);
  }
  if (iState.editor){
    input::stop_editor();
    gst.editor = !gst.editor;
    render::set_perspective(10.0f);
  }
  if (iState.debug){
    input::stop_debug();
    gst.debug = !gst.debug;
  }
  physics::update_ship_collision_state(gst.ship);
  if (gst.ship.state == world::SHIP_DESTORYED &&
      getExplosionPhase() == 0) {
    start_explosion_animation();
  }

  gst.player_won = (gst.ship.state == world::SHIP_LANDED);
  

  render::camera_follow_ship(gst.camera, gst.ship);
  explosion_idle(dt);
  render::idle_ship (dt, gst.player_won, gst.ship.thrusting, length (gst.ship.rotation));

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
  if (iState.debug){
    input::stop_debug();
    gst.debug = !gst.debug;
  }
  render::camera_follow_ship(gst.camera, gst.ship);
  
}

void game_update_editor() {
  core::time_update();
  input::InputState iState= input::get_input_state();
  if (iState.editor){
    input::stop_editor();
    gst.editor = !gst.editor;
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

  if (!gst.editor){
    render::draw_planet(gst.earth);
    render::draw_planet(gst.moon, &gst.ship.position);
    render::draw_planet(gst.sun);
  }

  if (gst.ship.state != world::SHIP_DESTORYED) {
    render::draw_ship(gst.ship);
  }
  if (gst.ship.state == world::SHIP_DESTORYED && getExplosionPhase() != 0) {
    render::draw_explosion(gst.ship);
    gst.ship.velocity.x = 0;
    gst.ship.velocity.y = 0;
    gst.ship.velocity.z = 0;
    gst.ship.angular_velocity.x = 0;
    gst.ship.angular_velocity.y = 0;
    gst.ship.angular_velocity.z = 0;
    gst.ship.thrust_power = 0;
  }
  if (gst.ship.state == world::SHIP_LANDED) {
    render::draw_text("Landing successful", 20,
                      ss.height - 70);
    render::draw_text("Press r to Restart", 20,
                      ss.height - 90);
    render::draw_important_text("YOU WIN !");
  } else if (gst.ship.state == world::SHIP_DESTORYED) {
    render::draw_text("Crash detected - Ship destroyed!", 20,
                      ss.height - 70);
    render::draw_text("Press r to Restart", 20,
                      ss.height - 90);
    render::draw_important_text("YOU LOSE !");
  }
  if (gst.pause) {
    render::draw_important_text("PAUSE");
  }
  if (!gst.editor){
    ui::draw_minimaps(gst.ship, gst.earth, gst.moon, gst.sun, gst.camera);
    if (gst.debug) {
      output::debug_camera(gst.camera.position.x, gst.camera.position.y,
                           gst.camera.position.z);
      output::debug_fps(gfps.fps);
    }
    draw_moon_transition_overlay();
  }
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
