#ifndef INPUT_INPUT
#define INPUT_INPUT

#include "../math/vec2.h"
#include <GL/glut.h>

namespace input {
struct InputState {
  Vec2 mouse_position;
  Vec2 mouse_delta;

  bool space_down;
};

void input_init();
void input_update();
const InputState &input_get_state();

} // namespace input

#endif