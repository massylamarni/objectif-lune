#ifndef RENDERER_RENDER_SETTINGS
#define RENDERER_RENDER_SETTINGS

#include "renderer.h"

namespace render {
typedef struct {
  bool gl_depth_test_toggle;
  bool gl_lighting_toggle;
  int gl_buffer_bit_mode;
  int gl_polygone_mode;
} render_settings;

typedef struct {
  bool prst_animation;
  int prst_animation_progress;
  int prst_animation_speed; // 16
  bool prst_auto_rotate;
  int prst_auto_rotate_speed;
  int prst_poly_count; // 16
} display_settings;

typedef struct {
  int prst_scale_value;
} object_property;

void apply_render_settings(const render_settings *rs);
} // namespace render

#endif
