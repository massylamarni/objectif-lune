#ifndef RENDERER_RENDER_SETTINGS
#define RENDERER_RENDER_SETTINGS

#include "renderer.h"

namespace render {
typedef struct {
  bool gl_line_toggle;
  bool gl_depth_test_toggle;
  bool gl_lighting_toggle;
  int prst_buffer_but_mode;
} render_settings;

void apply_render_settings(const render_settings *rs);
} // namespace render

#endif
