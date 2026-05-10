#include "start.h"
#include <cstdio>

static world::Planet moon;

static render::Camera camera;
static render::screen_settings &ss = render::get_screen_settings();
static float beta;
static float transparence;
static int phaseTransparence;
static float waitTransparence;

void start_init() {
  moon = world::create_planet(MOON_ID, Vec3(0, 0, 0), MOON_RADIUS, MOON_MASS);
  camera = render::create_camera(Vec3(0, 0, 1000), Vec3(0, 0, 0), CAMERA_UP);
  render::apply_perspective(59.0F, (float)ss.width/(float)ss.height);
  glutDisplayFunc(start_display);
  glutIdleFunc(start_update);
  glutKeyboardFunc(start_keyboard);
  float light_pos[4] = {0.0F, 0.0F, 1000.0F, 0.0f};
  glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  waitTransparence=0.0F;
  transparence=1.0F;
  phaseTransparence=1;
}

void phaseTransparence1(float dt){ 
  waitTransparence+=dt;
  if (waitTransparence>=10.0F){
    waitTransparence=0.0F;
    phaseTransparence=2;
  }
}

void phaseTransparence2(float dt){ 
  transparence-=dt;
  if (transparence<0.0F){
    transparence=0.0F;
    phaseTransparence=3;
  }
}

void phaseTransparence3(float dt){ 
  transparence+=dt;
  if (transparence>1.0F){
    transparence=1.0F;
    phaseTransparence=1;
  }
}

void start_update() { 
  core::time_update();
  float dt = core::time_delta();
  beta+=2.0F*dt;
  switch(phaseTransparence){
    case 1:
      phaseTransparence1(dt);
      break;
    case 2:
      phaseTransparence2(dt);
      break;
    case 3:
      phaseTransparence3(dt);
      break;
  }
  glutPostRedisplay();
}

void start_display() { render::display(start_display_hook); }

void start_display_hook() { 
  render::camera_apply(camera);
  glBindTexture(GL_TEXTURE_2D, 0);
  render::draw_title("OBJECTIF LUNE",ss.width/2-90,ss.height-50);
  render::draw_text_transparence("Press space to start",ss.width/2-80,50,transparence);
  glPushMatrix();
  glRotatef(beta,0.0F,1.0F,0.0F);
  render::draw_planet(moon);
  glPopMatrix();
}

void start_keyboard(unsigned char key, int x, int y) {
  if (key==' '){ 
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    game_init();
  }
  
}
