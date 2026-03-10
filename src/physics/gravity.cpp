#include "gravity.h"
#include <cstdio>

namespace physics {
void apply_planet_gravity(RigidBody &body, const world::Planet &planet) {
  Vec3 direction = planet.position - body.position;

  float distance = length(direction);
  printf("distance: %f\n", distance);

  if (distance <= 1.0f)
    return;

  Vec3 dir_normalized = direction / distance;

  float force_magnitude = planet.gravity * body.mass / (distance * distance);

  Vec3 force = dir_normalized * force_magnitude;

  rb_apply_force(body, force);
}
} // namespace physics