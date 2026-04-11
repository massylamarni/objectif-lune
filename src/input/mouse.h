#include "input.h"
#include "../render/renderer.h"

namespace input {
Vec2 window_center();
void warp_mouse_to_center();
void set_mouse_state(int x, int y);
void input_init_mouse();
} // namespace input