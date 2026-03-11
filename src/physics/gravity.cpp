#include "gravity.h"

namespace physics {
void apply_planet_gravity(RigidBody &body, const world::Planet &planet) {
  Vec3 direction = planet.position - body.position;
  float distance = length(direction);
  if (distance <= 1.0f) return;
  Vec3 dir_normalized = direction / distance;
  float force_magnitude = planet.gravity * body.mass / (distance * distance);
  Vec3 force = dir_normalized * force_magnitude;

  LOGD("Applying gravity of %s on %s with force: (x: %f, y: %f, z: %f)",
       ID_MAPPING[planet.id], ID_MAPPING[body.id], force.x, force.y, force.z);
  rb_apply_force(body, force);
}
} // namespace physics