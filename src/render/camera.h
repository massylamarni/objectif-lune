#ifndef RENDER_CAMERA
#define RENDER_CAMERA

#include "../world/ship.h"
#include <GL/glu.h>

namespace render {
struct Camera {
  Vec3 position;
  Vec3 target;
  Vec3 up;
};

Camera create_camera(Vec3 position, Vec3 target, Vec3 up);
void camera_apply(const Camera &cam);
void camera_follow_ship(Camera &cam, const world::Ship &ship);
} // namespace render

#endif
