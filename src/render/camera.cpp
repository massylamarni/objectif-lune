#include "camera.h"
#include "../world/world.h"
#include "../input/input.h"
#include <cmath>

namespace render {

Camera create_camera(Vec3 position, Vec3 target, Vec3 up) {
  Camera c;
  c.position = position;
  c.target = target;
  c.up = up;
  return c;
}

void camera_apply(const Camera &cam) {
  gluLookAt(cam.position.x, cam.position.y, cam.position.z, cam.target.x,
            cam.target.y, cam.target.z, cam.up.x, cam.up.y, cam.up.z);
}

void camera_follow_ship(Camera &cam, const world::Ship &ship) {
  input::InputState &state = input::get_input_state();
  Vec3 base_offset = SHIP_CAMERA_OFFSET;

  // Rotate offset by pitch around X first, then yaw around Y
  Vec3 rotated_offset = input::rotate_pitch(base_offset, state.mouse_rotation_delta.y);
  rotated_offset = input::rotate_yaw(rotated_offset, state.mouse_rotation_delta.x);

  cam.position = ship.position + rotated_offset;
  cam.target = ship.position;
  cam.up = Vec3(0, 1, 0);
}
} // namespace render