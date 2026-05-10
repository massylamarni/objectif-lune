#include "debug.h"

namespace output {
static render::screen_settings &ss = render::get_screen_settings();

void debug_camera(float x, float y, float z) {
  glBindTexture(GL_TEXTURE_2D, NULL);
  const int SECTION_MAX_WIDTH = 250;
  char buf[128];
  snprintf(buf, sizeof(buf), "cam (%.1f, %.1f, %.1f)", x, y, z);
  render::draw_text(buf, ss.width - SECTION_MAX_WIDTH - DEBUG_MARGIN,
                    ss.height - DEBUG_MARGIN);
}

void debug_fps(float fps) {
  char buf[128];
  snprintf(buf, sizeof(buf), "FPS: %.1f", fps);
  render::draw_text(buf, DEBUG_MARGIN, ss.height - DEBUG_MARGIN);
}

void debug_ship_state(const world::Ship ship) {
  const int SECTION_MAX_WIDTH = 250;
  const int CURRENT_LINE_COUNT = 3;
  const Vec3 attr[] = {ship.position, ship.velocity, ship.angular_velocity,
                       ship.rotation};
  const char labels[4][64] = {"Position", "Velocity", "Angular velocity",
                              "Rotation"};

  const int labels_len = 4;
  for (int i = 0; i < labels_len; i++) {
    char buf[128];
    snprintf(buf, sizeof(buf), "%s: (%.1f, %.1f, %.1f)", labels[i], attr[i].x,
             attr[i].y, attr[i].z);
    render::draw_text(buf, ss.width - SECTION_MAX_WIDTH - DEBUG_MARGIN,
                      ss.height -
                          (DEBUG_LINE_MAX_HEIGHT * (CURRENT_LINE_COUNT + i)));
  }
}

void debug_controls(/* hardcoded */) {
  const int SECTION_MAX_WIDTH = 350;
  const int CURRENT_LINE_COUNT = 0;
  const char labels[16][64] = {"qzsd - Left/Forward/Backward/Right",
                               "ae - Down/Up",
                               "p - Pause",
                               "r - Restart",
                               "SPACE - Thrust",
                               "LMB(hold) - Move camera",
                               "RMB(click) - Ship pitch/yaw",
                               "u - Toggle minimap view",
                               "v - Toggle model view",
                               "h - Toggle GL_DEPTH_TEST",
                               "H - Toggle GL_CULL_FACE",
                               "l - Toggle GL_LIGHTING",
                               "L - Toggle GL_COLOR_MATERIAL",
                               "o - Switch GL_FILL, GL_LINE, GL_POINT",
                               "O - Switch GL_DEPTH_BUFFER_BIT,",
                               "       GL_COLOR_BUFFER_BIT"};

  const int labels_len = 16;
  for (int i = 0; i < labels_len; i++) {
    char buf[128];
    snprintf(buf, sizeof(buf), "%s", labels[i]);
    render::draw_text(buf, ss.width - SECTION_MAX_WIDTH - DEBUG_MARGIN,
                      DEBUG_MARGIN +
                          (DEBUG_LINE_MAX_HEIGHT *
                           (CURRENT_LINE_COUNT + (labels_len - 1 - i))));
  }
}

void hint_debug() {
  glBindTexture(GL_TEXTURE_2D, NULL);
  const int SECTION_MAX_WIDTH = 200;

  char buf[128];
  snprintf(buf, sizeof(buf), "Press f to toggle debug...");
  render::draw_text(buf, ss.width - SECTION_MAX_WIDTH - DEBUG_MARGIN,
                    DEBUG_MARGIN);
}

} // namespace output
