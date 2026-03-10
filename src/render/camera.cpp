#include "camera.h"
#include "../world/world.h"

namespace render {
void camera_apply(const Camera &cam) {
  gluLookAt(cam.position.x, cam.position.y, cam.position.z,

            cam.target.x, cam.target.y, cam.target.z,

            cam.up.x, cam.up.y, cam.up.z);
}

void camera_follow_ship(Camera &cam, const world::Ship &ship) {
  cam.target = ship.position;
  cam.position = ship.position + SHIP_CAMERA_OFFSET;

  cam.up = Vec3(0, 1, 0);
}
} // namespace render