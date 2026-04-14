#include "input.h"
#include "keyboard.h"
#include "mouse.h"
#include "../ui/minimap.h"
#include "../world/world.h"

namespace input {
static InputState state;

void set_key_state(unsigned char key, int x, int y, int isDown) {
  switch (key) {
    case ' ': state.space_down = isDown; break;
    case 'a': state.a_down = isDown; break;
    case 'z': state.z_down = isDown; break;
    case 'e': state.e_down = isDown; break;
    case 'q': state.q_down = isDown; break;
    case 's': state.s_down = isDown; break;
    case 'd': state.d_down = isDown; break;
    case 'u': state.u_down = isDown; break;
  }
}

void keyboard_callback(unsigned char key, int x, int y) {
  // printf("K  %4d %4d %4d\n",specialKey,x,y);
  set_key_state(key, x, y, true);
}

void keyboard_up_callback(unsigned char key, int x, int y) {
  // printf("KUP  %4d %4d %4d\n",specialKey,x,y);
  set_key_state(key, x, y, false);
}

void special_callback(int specialKey, int x, int y) {
  // printf("S  %4d %4d %4d\n",specialKey,x,y);
}

void mouse_callback(int button, int state, int x, int y) {
  // printf("M  %4d %4d %4d %4d\n",button,state,x,y);
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

void input_update(Vec3 &vec3) {
  if (state.q_down) vec3 += rotate_yaw(Vec3(-INPUT_VEC3_UPDATE_VALUE, 0, 0), state.mouse_rotation_delta.x);
  if (state.d_down) vec3 += rotate_yaw(Vec3(INPUT_VEC3_UPDATE_VALUE, 0, 0), state.mouse_rotation_delta.x);
  if (state.a_down) vec3.y -= INPUT_VEC3_UPDATE_VALUE;
  if (state.e_down) vec3.y += INPUT_VEC3_UPDATE_VALUE;
  if (state.z_down) vec3 += rotate_yaw(Vec3(0, 0, -INPUT_VEC3_UPDATE_VALUE), state.mouse_rotation_delta.x);
  if (state.s_down) vec3 += rotate_yaw(Vec3(0, 0, INPUT_VEC3_UPDATE_VALUE), state.mouse_rotation_delta.x);
  ui::toggle_orbit_main_view(state.u_down);
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

} // namespace input