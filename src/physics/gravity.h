#ifndef PHYSICS_GRAVITY
#define PHYSICS_GRAVITY

#include "../output/logs.h"
#include "../world/planet.h"
#include "../world/world.h"
#include "rigidbody.h"
#include <cmath>
#include <cstdio>

namespace physics {
void apply_planet_gravity(RigidBody &body, const world::Planet &planet);
} // namespace physics

#endif