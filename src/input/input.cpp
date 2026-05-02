#include "input.h"
#include "../ui/minimap.h"
#include "../world/world.h"
#include "keyboard.h"
#include "mouse.h"

namespace input {
static InputState state;

void set_key_state(unsigned char key, int x, int y, int isDown) {
  switch (key) {
  case ' ':
    state.space_down = isDown;
    break;
  case 'a':
    state.a_down = isDown;
    break;
  case 'z':
    state.z_down = isDown;
    break;
  case 'e':
    state.e_down = isDown;
    break;
  case 'q':
    state.q_down = isDown;
    break;
  case 's':
    state.s_down = isDown;
    break;
  case 'd':
    state.d_down = isDown;
    break;
  case 'u':
    state.u_down = isDown;
    break;
  case 'r':
    state.r_down = isDown;
    break;
  case 'f':
    if (!state.f_down && isDown)
      state.debug = true;
    state.p_down = isDown;
    break;
  case 'p':
    if (!state.p_down && isDown)
      state.pause = true;
    state.p_down = isDown;
    break;
  case 'v':
    if (!state.v_down && isDown)
      state.editor = true;
    state.v_down = isDown;
    break;
  }
}

void keyboard_callback(unsigned char key, int x, int y) {
  // printf("K  %4d %4d %4d\n",specialKey,x,y);
  set_key_state(key, x, y, true);
  set_global_keyboard_listeners(key, x, y, render::model_proprty());
}

void keyboard_up_callback(unsigned char key, int x, int y) {
  // printf("KUP  %4d %4d %4d\n",specialKey,x,y);
  set_key_state(key, x, y, false);
}

void special_callback(int specialKey, int x, int y) {
  // printf("S  %4d %4d %4d\n",specialKey,x,y);
  set_global_keyboard_listeners_s(specialKey, x, y, render::model_proprty());
}

void mouse_callback(int button, int state, int x, int y) {
  // printf("M  %4d %4d %4d %4d\n",button,state,x,y);
  InputState &s = get_input_state();
  if (button == GLUT_LEFT_BUTTON) {
    if (state == GLUT_DOWN) {
      s.lmb_down = true;
      glutSetCursor(GLUT_CURSOR_NONE);
      warp_mouse_to_center();
    } else {
      s.lmb_down = false;
      glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
    }
  } else if (button == GLUT_RIGHT_BUTTON) {
    if (s.lmb_down) {
      s.rmb_down = false;
    } else {
      s.rmb_down = (state == GLUT_DOWN);
    }
  }
}

void mouse_motion_callback(int x, int y) {
  // printf("MM %4d %4d\n",x,y);
  set_mouse_state(x, y);
}

void mouse_passive_motion_callback(int x, int y) {
  // printf("PM %4d %4d\n",x,y);
  set_mouse_state(x, y);
}

void input_init() {
  input_init_mouse();
  input_init_keyboard();

  glutKeyboardFunc(keyboard_callback);
  glutKeyboardUpFunc(keyboard_up_callback);
  glutSpecialFunc(special_callback);
  glutMouseFunc(mouse_callback);
  glutMotionFunc(mouse_motion_callback);
  glutPassiveMotionFunc(mouse_passive_motion_callback);
}

void input_update(world::Ship &ship, float dt) {
  if (state.q_down)
    ship.velocity += rotate_yaw(Vec3(-INPUT_VEC3_UPDATE_VALUE, 0, 0),
                                state.mouse_rotation_delta.x);
  if (state.d_down)
    ship.velocity += rotate_yaw(Vec3(INPUT_VEC3_UPDATE_VALUE, 0, 0),
                                state.mouse_rotation_delta.x);
  if (state.a_down)
    ship.velocity.y -= INPUT_VEC3_UPDATE_VALUE;
  if (state.e_down)
    ship.velocity.y += INPUT_VEC3_UPDATE_VALUE;
  if (state.z_down)
    ship.velocity += rotate_yaw(Vec3(0, 0, -INPUT_VEC3_UPDATE_VALUE),
                                state.mouse_rotation_delta.x);
  if (state.s_down)
    ship.velocity += rotate_yaw(Vec3(0, 0, INPUT_VEC3_UPDATE_VALUE),
                                state.mouse_rotation_delta.x);
  ui::toggle_orbit_main_view(state.u_down);

  // ship.thrusting = (state.rmb_down && !state.lmb_down);
  ship.thrusting = state.space_down;
  if (state.rmb_down && !state.lmb_down) {
    Vec2 p = state.mouse_abs;
    float dist = sqrtf(p.x * p.x + p.y * p.y);
    const float r_max = 300.0f;
    if (dist > r_max)
      dist = r_max;
    const float ROT_GAIN = 0.000005f;
    float ang = ROT_GAIN * dist * dist;
    float dirx = (dist > 0.0f) ? (p.x / dist) : 0.0f;
    float diry = (dist > 0.0f) ? (p.y / dist) : 0.0f;
    ship.angular_velocity.y = dirx * ang;
    ship.angular_velocity.x = -diry * ang;
    // ship.angular_velocity.z
  }
}

Vec3 rotate_yaw(const Vec3 &v, float yaw) {
  float cos_y = cos(yaw);
  float sin_y = sin(yaw);
  return Vec3(v.x * cos_y - v.z * sin_y, v.y, v.x * sin_y + v.z * cos_y);
}

Vec3 rotate_pitch(const Vec3 &v, float pitch) {
  float cos_p = cos(pitch);
  float sin_p = sin(pitch);
  return Vec3(v.x, v.y * cos_p - v.z * sin_p, v.y * sin_p + v.z * cos_p);
}

InputState &get_input_state() { return state; }

void stop_pause() { state.pause = false; }

void stop_debug() { state.debug = false; }

void stop_editor() { state.editor = false; }

void stop_mouse_input(bool stop) {
  if (stop) {
    glutMouseFunc(NULL);
    glutMotionFunc(NULL);
    glutPassiveMotionFunc(NULL);
  } else {
    glutMouseFunc(mouse_callback);
    glutMotionFunc(mouse_motion_callback);
    glutPassiveMotionFunc(mouse_passive_motion_callback);
  }
}

void simulate_camera_swipe(float pixels, Vec2 axis) {
  InputState &state = get_input_state();
  state.lmb_down = true;
  if (axis.x) state.mouse_rotation_delta.x += pixels * MOUSE_SENSITIVITY;
  if (axis.y) state.mouse_rotation_delta.y += pixels * MOUSE_SENSITIVITY;
  state.lmb_down = false;
}

} // namespace input
