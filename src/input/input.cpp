#include "input.h"

namespace input {
static InputState state;

static int last_mouse_x = 0;
static int last_mouse_y = 0;

void mouse_motion_callback(int x, int y) {
  state.mouse_position.x = (float)x;
  state.mouse_position.y = (float)y;

  state.mouse_delta.x = (float)(x - last_mouse_x);
  state.mouse_delta.y = (float)(y - last_mouse_y);

  last_mouse_x = x;
  last_mouse_y = y;
}

void keyboard_down_callback(unsigned char key, int x, int y) {
  if (key == ' ')
    state.space_down = true;
}

void keyboard_up_callback(unsigned char key, int x, int y) {
  if (key == ' ')
    state.space_down = false;
}

void input_init() {
  state.mouse_position = Vec2(0, 0);
  state.mouse_delta = Vec2(0, 0);
  state.space_down = false;

  glutPassiveMotionFunc(mouse_motion_callback);
  glutKeyboardFunc(keyboard_down_callback);
  glutKeyboardUpFunc(keyboard_up_callback);
}

void input_update() { state.mouse_delta = Vec2(0, 0); }

const InputState &input_get_state() { return state; }

} // namespace input