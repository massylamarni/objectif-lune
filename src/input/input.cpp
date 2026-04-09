#include "input.h"

namespace input {
static InputState state;

static int last_mouse_x = 0;
static int last_mouse_y = 0;

void set_mouse_state(int x, int y) {
  state.mouse_position.x = (float)x;
  state.mouse_position.y = (float)y;

  state.mouse_delta.x = (float)(x - last_mouse_x);
  state.mouse_delta.y = (float)(y - last_mouse_y);

  last_mouse_x = x;
  last_mouse_y = y;
}

void set_key_state(unsigned char key, int x, int y, int isDown) {
  switch (key) {
    case ' ': state.space_down = isDown; break;
    case 'a': state.a_down = isDown; break;
    case 'z': state.z_down = isDown; break;
    case 'e': state.e_down = isDown; break;
    case 'q': state.q_down = isDown; break;
    case 's': state.s_down = isDown; break;
    case 'd': state.d_down = isDown; break;
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
}

void input_init() {
  state.mouse_position = Vec2(0, 0);
  state.mouse_delta = Vec2(0, 0);
  state.space_down = false;
  state.a_down = false;
  state.z_down = false;
  state.e_down = false;
  state.q_down = false;
  state.s_down = false;
  state.d_down = false;

  glutKeyboardFunc(keyboard_callback);
  glutKeyboardUpFunc(keyboard_up_callback);
  glutSpecialFunc(special_callback);
  glutMouseFunc(mouse_callback);
  glutMotionFunc(mouse_motion_callback);
  glutPassiveMotionFunc(mouse_passive_motion_callback);
}

void input_update(Vec3 &position) {
  //state.mouse_delta = Vec2(0, 0);
  const int UPDATE_SPEED = 1;
  if (state.q_down) position.x -= UPDATE_SPEED;
  if (state.d_down) position.x += UPDATE_SPEED;
  if (state.a_down) position.y -= UPDATE_SPEED;
  if (state.e_down) position.y += UPDATE_SPEED;
  if (state.z_down) position.z -= UPDATE_SPEED;
  if (state.s_down) position.z += UPDATE_SPEED;
}

const InputState &get_input_state() { return state; }

} // namespace input