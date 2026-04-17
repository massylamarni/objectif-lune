#ifndef INPUT_INPUT
#define INPUT_INPUT

#include "../math/vec2.h"
#include "../math/vec3.h"

#include <GL/glut.h>

namespace input {
struct InputState {
  Vec2 mouse_rotation_delta;
  Vec2 mouse_delta;

  bool space_down;
  bool a_down;
  bool z_down;
  bool e_down;
  bool q_down;
  bool s_down;
  bool d_down;
  bool u_down;
  bool r_down;
};

void input_init();
void input_update(Vec3 &vec3, Vec3 &rotation);
Vec3 rotate_yaw(const Vec3 &v, float yaw);
Vec3 rotate_pitch(const Vec3 &v, float pitch);
InputState &get_input_state();

} // namespace input

#endif
