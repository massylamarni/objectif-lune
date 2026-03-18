#include "renderer_settings.h"

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

  if (rs->gl_line_toggle)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  else
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  if (rs->gl_depth_test_toggle)
    glEnable(GL_DEPTH_TEST);
  else
    glDisable(GL_DEPTH_TEST);

  if (rs->gl_lighting_toggle)
    glEnable(GL_LIGHTING);
  else
    glDisable(GL_LIGHTING);

  if (rs->prst_buffer_but_mode == 0)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  else if (rs->prst_buffer_but_mode == 1)
    glClear(GL_DEPTH_BUFFER_BIT);
  else if (rs->prst_buffer_but_mode == 2)
    glClear(GL_COLOR_BUFFER_BIT);
}
} // namespace render