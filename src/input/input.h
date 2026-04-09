#ifndef INPUT_INPUT
#define INPUT_INPUT

#include "../math/vec2.h"
#include "../math/vec3.h"

#include <GL/glut.h>

namespace input {
struct InputState {
  Vec2 mouse_position;
  Vec2 mouse_delta;

  bool space_down;
  bool a_down;
  bool z_down;
  bool e_down;
  bool q_down;
  bool s_down;
  bool d_down;
};

void input_init();
void input_update(Vec3 &position);
const InputState &get_input_state();

} // namespace input

#endif