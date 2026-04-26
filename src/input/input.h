#ifndef INPUT_INPUT
#define INPUT_INPUT

#include "../math/vec2.h"
#include "../math/vec3.h"

#include <GL/glut.h>
#include "../world/ship.h"

namespace input {
struct InputState {
  Vec2 mouse_rotation_delta;
  Vec2 mouse_delta;
  Vec2 mouse_abs;

  bool lmb_down;
  bool rmb_down;

  bool space_down;
  bool a_down;
  bool z_down;
  bool e_down;
  bool q_down;
  bool s_down;
  bool d_down;
  bool u_down;
  bool r_down;
  bool p_down;
  bool pause;
};

void input_init();
void input_update(world::Ship &ship, float dt);
Vec3 rotate_yaw(const Vec3 &v, float yaw);
Vec3 rotate_pitch(const Vec3 &v, float pitch);
InputState &get_input_state();
void stop_pause();
void stop_mouse_input(bool stop);

} // namespace input

#endif
