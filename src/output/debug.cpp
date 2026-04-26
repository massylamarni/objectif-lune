#include "debug.h"

namespace output {
static render::screen_settings ss = render::get_screen_settings();

void debug_camera(float x, float y, float z) {
  char buf[128];
  snprintf(buf, sizeof(buf), "cam (%.1f, %.1f, %.1f)", x, y, z);
  int textWidth = 200;
  render::draw_text(buf, ss.width - textWidth - DEBUG_CAMERA_MARGIN, ss.height - DEBUG_CAMERA_MARGIN);
}

void debug_fps(float fps) {
  char buf[128];
  snprintf(buf, sizeof(buf), "FPS: %.1f", fps);
  render::draw_text(buf, DEBUG_CAMERA_MARGIN, ss.height - DEBUG_CAMERA_MARGIN);
}
} // namespace render


