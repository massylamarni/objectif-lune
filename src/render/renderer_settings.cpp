#include "renderer_settings.h"
#include "../input/utils.h"

namespace render {
void apply_render_settings(const render_settings *rs) {
  static float alpha_x = 0.0F;
  static float alpha_y = 0.0F;
  static float alpha_z = 0.0F;

  static int prev_x = 0;
  static int prev_y = 0;
  static int poly_count_step = 1;
  static int poly_count_x = 72;
  static int poly_count_y = 180;

  gltoggle_macro(GL_DEPTH_TEST);
  gltoggle_macro(GL_LIGHTING);
  gltoggle_macro(GL_LIGHTING);
  gltoggle_macros((int[]){GL_FILL, GL_LINE, GL_POINT});

  if (rs->gl_polygone_mode == 0)
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  else if (rs->gl_polygone_mode == 1)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  else if (rs->gl_polygone_mode == 2)
    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

  if (rs->gl_buffer_bit_mode == 0)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  else if (rs->gl_buffer_bit_mode == 1)
    glClear(GL_DEPTH_BUFFER_BIT);
  else if (rs->gl_buffer_bit_mode == 2)
    glClear(GL_COLOR_BUFFER_BIT);
}
} // namespace render