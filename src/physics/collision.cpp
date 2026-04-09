#include "collision.h"

namespace physics {
bool check_planet_collision(const RigidBody &body, const world::Planet &planet) {
  Vec3 diff = body.position - planet.position;
  float dist = length(diff);
  return dist <= planet.radius + body.radius;
}

void resolve_planet_collision(RigidBody &body, const world::Planet &planet) {
  Vec3 normal = normalize(body.position - planet.position);
  body.position = planet.position + normal * (planet.radius + body.radius);
  float velocity_normal = dot(body.velocity, normal);
  if (velocity_normal < 0.0f) {
    body.velocity -= normal * velocity_normal;
  }
}
} // namespace physics