#ifndef UI_MINIMAP
#define UI_MINIMAP

#include "../render/camera.h"
#include "../world/planet.h"
#include "../world/ship.h"

#define MINIMAP_1_FOV_DEG 52.0f
#define LANDING_TRIGGER_MULTIPLIER 1.6f
#define MINIMAP_MARGINS 15
#define TRAIL_LENGTH 100.0f
#define TRAIL_SENSITIVITY 5.0f
#define TRAIL_MIN_LEN 50
#define TRAIL_MAX_LEN 300
#define TRAIL_WIDTH 2.0f


namespace ui {
struct MinimapViewport {
  int x;
  int y;
  int width;
  int height;
};

void toggle_orbit_main_view(bool key_state);
bool is_orbit_main_view_enabled();
void draw_minimaps(const world::Ship &ship, const world::Planet &earth,
                   const world::Planet &moon, const world::Planet &sun,
                   const render::Camera &game_camera);
void reset_orbit_trail();
} // namespace ui

#endif