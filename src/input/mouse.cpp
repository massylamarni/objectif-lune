#include "mouse.h"

namespace input {
static int last_mouse_x = 0;
static int last_mouse_y = 0;
static bool ignore_warp_event = false;

Vec2 window_center() {
  return Vec2(render::SCREEN_WIDTH * 0.5f, render::SCREEN_HEIGHT * 0.5f);
}

void warp_mouse_to_center() {
  Vec2 center = window_center();
  if (center.x > 0 && center.y > 0) {
    ignore_warp_event = true;
    glutWarpPointer((int)center.x, (int)center.y);
    last_mouse_x = (int)center.x;
    last_mouse_y = (int)center.y;
  }
}

void set_mouse_state(int x, int y) {
  InputState &state = get_input_state();
  Vec2 center = window_center();
  if (ignore_warp_event && x == last_mouse_x && y == last_mouse_y) {
    ignore_warp_event = false;
    return;
  }

  state.mouse_delta.x = (float)(x - center.x);
  state.mouse_delta.y = (float)(center.y - y);

  if (center.x > 0 && center.y > 0) {
    const float MOUSE_SENSITIVITY = 0.005f; // radians per pixel
    state.mouse_rotation_delta.x += state.mouse_delta.x * MOUSE_SENSITIVITY;
    state.mouse_rotation_delta.y += state.mouse_delta.y * MOUSE_SENSITIVITY;

    if (state.mouse_rotation_delta.y > M_PI / 2.0f - 0.1f)
      state.mouse_rotation_delta.y = M_PI / 2.0f - 0.1f;
    if (state.mouse_rotation_delta.y < -M_PI / 2.0f + 0.1f)
      state.mouse_rotation_delta.y = -M_PI / 2.0f + 0.1f;
  }

  warp_mouse_to_center();
}

void input_init_mouse() {
  InputState &state = get_input_state();
  state.mouse_rotation_delta = Vec2(0, 0);
  state.mouse_delta = Vec2(0, 0);

  Vec2 center = window_center();
  last_mouse_x = (int)center.x;
  last_mouse_y = (int)center.y;
  glutSetCursor(GLUT_CURSOR_NONE);
  warp_mouse_to_center();
}
} // namespace input