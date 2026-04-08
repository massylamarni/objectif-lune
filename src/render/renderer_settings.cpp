#include "renderer_settings.h"
#include "../input/utils.h"

namespace render {
model_proprty init_model_property() {
  display_settings ds = {0.5, 16, 0, 16, 0, false, false, 3};
  scene_property sp = {0};
  object_property op = {1};

  model_proprty mp = {ds, sp, op};
  return mp;
}

void apply_render_settings(const render_settings *rs) {
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