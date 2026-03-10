#ifndef PHYSICS_COLLISION
#define PHYSICS_COLLISION

#include "../world/planet.h"
#include "rigidbody.h"

namespace physics {
bool check_planet_collision(const RigidBody &body, const world::Planet &planet);
void resolve_planet_collision(RigidBody &body, const world::Planet &planet);
} // namespace physics

#endif
