#ifndef OUTPUT_DEBUG
#define OUTPUT_DEBUG

#include "../render/renderer.h"
#include "../render/utils.h"

#define DEBUG_CAMERA_MARGIN 30

namespace output {
void debug_camera(float x, float y, float z);
void debug_fps(float fps);
} // namespace render


#endif