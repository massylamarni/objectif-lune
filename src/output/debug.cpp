#include "debug.h"

namespace output {
void debug_camera(float x, float y, float z) {
  char buf[128];
  snprintf(buf, sizeof(buf), "cam (%.1f, %.1f, %.1f)", x, y, z);
  int textWidth = 200;
  render::draw_text(buf, render::SCREEN_WIDTH - textWidth - DEBUG_CAMERA_MARGIN, render::SCREEN_HEIGHT - DEBUG_CAMERA_MARGIN);
}

void debug_fps(float fps) {
  char buf[128];
  snprintf(buf, sizeof(buf), "FPS: %.1f", fps);
  int textWidth = 100;
  render::draw_text(buf, DEBUG_CAMERA_MARGIN, render::SCREEN_HEIGHT - DEBUG_CAMERA_MARGIN);
}
} // namespace render


