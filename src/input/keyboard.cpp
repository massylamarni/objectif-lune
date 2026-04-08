#include "keyboard.h"
#include <GL/gl.h>

void set_global_keyboard_listeners(unsigned char key, int x, int y) {
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

  float prst_fov = 0;
  float prst_polygon_count = 0;
  float prst_scene_id = 0;
  float prst_size = 0;

  key_to_float_map ktof[] = {
      {'B', 'b', &prst_fov, 0, 4.4, 0.1, false},
      {'M', 'm', &prst_polygon_count, 3, 1024, 1, false},
      {'N', 'n', &prst_scene_id, 0.01, 10, 0.01, false},
      {'M', 'm', &prst_size, 0, 3, 1, true},
  };

  size_t ktom_len = 4;
  size_t ktoms_len = 1;
  size_t ktoms_2p_len = 1;
  size_t ktof_len = 4;

  for (int i = 0; i < ktom_len; i++) {
    gltoggle_on_key_press(ktom[i].macro, key, ktom[i].key);
  }
  for (int i = 0; i < ktoms_len; i++) {
    glswitch_macros(ktoms[i].macros, ktoms_len, glClear, key, ktoms[i].key[0],
                    ktoms[i].key[1]);
  }
  for (int i = 0; i < ktoms_2p_len; i++) {
    glswitch_macros_2p(GL_FRONT_AND_BACK, ktoms_2p[i].macros, ktoms_2p_len,
                       glPolygonMode, key, ktoms_2p[i].key[0],
                       ktoms_2p[i].key[1]);
  }
  for (int i = 0; i < ktof_len; i++) {
    update_on_key_press(ktof[i].fptr, key, ktof[i].key[0], ktof[i].key[1],
                        ktof[i].min_value, ktof[i].max_value, ktof[i].step,
                        ktof[i].is_wrapped);
  }
}