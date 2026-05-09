#ifndef OUTPUT_DEBUG
#define OUTPUT_DEBUG

#include "../render/renderer.h"
#include "../render/utils.h"
#include "../world/ship.h"

#define DEBUG_MARGIN 30
#define DEBUG_LINE_MAX_HEIGHT 20


namespace output {
void debug_camera(float x, float y, float z);
void debug_fps(float fps);
void debug_ship_state(const world::Ship ship);
void debug_controls(/* hardcoded */);
void hint_debug();
} // namespace render


#endif