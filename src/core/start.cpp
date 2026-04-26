#include "start.h"
#include <cstdio>

static world::Planet moon;

static render::Camera camera;
render::screen_settings ss = render::get_screen_settings();

void start_init() {
  moon = world::create_planet(MOON_ID, Vec3(0, 0, 0), MOON_RADIUS, MOON_MASS);
  camera = render::create_camera(Vec3(0, 0, 1000), Vec3(0, 0, 0), CAMERA_UP);
  render::set_perspective(59.0F);
  glutDisplayFunc(start_display);
  glutIdleFunc(start_update);
  glutKeyboardFunc(start_keyboard);
  float light_pos[4] = {0.0F, 0.0F, 1000.0F, 0.0f};
  glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void start_update() { 
}

void start_display() { render::display(start_display_hook); }

void start_display_hook() { 
  render::camera_apply(camera);
  render::draw_planet(moon);
  render::draw_title("OBJECTIF LUNE",ss.width/2-80,ss.height-50);
  render::draw_text("Press space to start",ss.width/2-80,50);
}

void start_keyboard(unsigned char key, int x, int y) {
  if (key==' '){ 
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    game_init();
  }
  
}
