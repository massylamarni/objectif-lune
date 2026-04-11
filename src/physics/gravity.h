#ifndef PHYSICS_GRAVITY
#define PHYSICS_GRAVITY

#include "../output/logs.h"
#include "../world/planet.h"
#include "rigidbody.h"
#include <cmath>
#include <cstdio>

#define G 1.0f

namespace physics {
void apply_planet_gravity(RigidBody &body, const world::Planet &planet);
} // namespace physics

#endif