#ifndef PHYSICS_GRAVITY
#define PHYSICS_GRAVITY

#include "../world/planet.h"
#include "rigidbody.h"
#include <cmath>

namespace physics {
void apply_planet_gravity(RigidBody &body, const world::Planet &planet);
} // namespace physics

#endif