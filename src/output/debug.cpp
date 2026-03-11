#include "debug.h"

namespace output {
void debug_camera(float x, float y, float z) {
  char buf[128];
  snprintf(buf, sizeof(buf), "cam (%.1f, %.1f, %.1f)", x, y, z);
  const int margin = 30;
  int textWidth = 200;
  render::draw_text(buf, render::SCREEN_WIDTH - textWidth - margin, render::SCREEN_HEIGHT - margin);
}
} // namespace render


