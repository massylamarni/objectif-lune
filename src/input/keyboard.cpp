#include "keyboard.h"
#include "input.h"
#include <GL/gl.h>
#include <cstddef>

namespace input {
void set_global_keyboard_listeners(unsigned char key, int x, int y,
                                   render::model_proprty mp) {
  key_to_macro_map ktom[] = {{'h', GL_DEPTH_TEST},
                             {'H', GL_CULL_FACE},
                             {'l', GL_LIGHTING},
                             {'L', GL_COLOR_MATERIAL}};
  key_to_macros_map ktoms[] = {
      {'P',
       '\0',
       {GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, GL_DEPTH_BUFFER_BIT,
        GL_COLOR_BUFFER_BIT}},
  };
  key_to_macros_map ktoms_2p[] = {
      {'p', '\0', {GL_FILL, GL_LINE, GL_POINT}},
  };

  key_to_float_map ktof[] = {
      {'B', 'b', &mp.ds.fov, 0, 4.4, 0.1, 1, false},
      {'M', 'm', &mp.ds.poly_count, 3, 1024, 1, 1, false},
      {'N', 'n', &mp.op.scale_value, 0.01, 10, 0.01, 1, false},
      {'M', 'm', &mp.sp.scene_id, 0, 3, 1, 1, true},
  };

  key_to_float_map ktof_proportional[] = {
      {GLUT_KEY_INSERT, 0x7f, &mp.ds.fov, -3600, 3600, 0.05, 0.05, false},
  };

  size_t ktom_len = 4;
  size_t ktoms_len = 1;
  size_t ktoms_2p_len = 1;
  size_t ktof_len = 4;
  size_t ktof_proportional_len = 1;

  /* --- */

  for (size_t i = 0; i < ktom_len; i++) {
    gltoggle_on_key_press(ktom[i].macro, key, ktom[i].key);
  }
  for (size_t i = 0; i < ktoms_len; i++) {
    glswitch_macros(ktoms[i].macros, ktoms_len, glClear, key, ktoms[i].key[0],
                    ktoms[i].key[1]);
  }
  for (size_t i = 0; i < ktoms_2p_len; i++) {
    glswitch_macros_2p(GL_FRONT_AND_BACK, ktoms_2p[i].macros, ktoms_2p_len,
                       glPolygonMode, key, ktoms_2p[i].key[0],
                       ktoms_2p[i].key[1]);
  }
  for (size_t i = 0; i < ktof_len; i++) {
    update_on_key_press(ktof[i].fptr, key, ktof[i].key[0], ktof[i].key[1],
                        ktof[i].min_value, ktof[i].max_value, ktof[i].step,
                        ktof[i].is_wrapped);
  }
  for (size_t i = 0; i < ktof_proportional_len; i++) {
    update_on_key_press_proportional(
        ktof_proportional[i].fptr, key, ktof_proportional[i].key[0],
        ktof_proportional[i].key[1], ktof_proportional[i].min_value,
        ktof_proportional[i].max_value, ktof_proportional[i].step,
        ktof_proportional[i].step_factor, ktof_proportional[i].is_wrapped);
  }
}

void set_global_keyboard_listeners_s(unsigned char key, int x, int y,
                                     render::model_proprty mp) {
  input::InputState &is = input::get_input_state();

  key_to_float_map ktofs[] = {
      {GLUT_KEY_PAGE_UP, GLUT_KEY_PAGE_DOWN, &mp.ds.animation_speed, 0, 100, 1,
       1, false},
      {GLUT_KEY_INSERT, GLUT_KEY_PAGE_DOWN, &mp.ds.rotation_speed, 0, 100, 1, 1,
       false},
      {GLUT_KEY_RIGHT, GLUT_KEY_LEFT, &is.mouse_rotation_delta.x, 0, 100,
       mp.ds.camera_speed, 1, false},
      {GLUT_KEY_UP, GLUT_KEY_DOWN, &is.mouse_rotation_delta.y, 0, 100,
       mp.ds.camera_speed, 1, true},
  };

  key_to_float_map ktof_proportional_s[] = {
      {GLUT_KEY_HOME, GLUT_KEY_END, &mp.ds.camera_speed, 0, 3600, 0, 0.05,
       false},
      {GLUT_KEY_INSERT, 0x7f, &mp.ds.rotation_speed, -3600, 3600, 0.05, 0.05,
       false},
  };

  size_t ktof_s_len = 4;
  size_t ktof_proportional_s_len = 2;

  /* --- */

  for (size_t i = 0; i < ktof_proportional_s_len; i++) {
    update_on_key_press_proportional(
        ktof_proportional_s[i].fptr, key, ktof_proportional_s[i].key[0],
        ktof_proportional_s[i].key[1], ktof_proportional_s[i].min_value,
        ktof_proportional_s[i].max_value, ktof_proportional_s[i].step,
        ktof_proportional_s[i].step_factor, ktof_proportional_s[i].is_wrapped);
  }
}

void input_init_keyboard() {
  InputState &state = get_input_state();
  state.space_down = false;
  state.a_down = false;
  state.z_down = false;
  state.e_down = false;
  state.q_down = false;
  state.s_down = false;
  state.d_down = false;
  state.u_down = false;
  state.r_down = false;
  state.f_down = false;
  state.p_down = false;
  state.pause = false;
  state.debug = false;
}
} // namespace input
