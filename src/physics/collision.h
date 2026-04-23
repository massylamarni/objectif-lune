#ifndef PHYSICS_COLLISION
#define PHYSICS_COLLISION

#include "../world/planet.h"
#include "../world/ship.h"
#include "rigidbody.h"

#define CRASH_SPEED_THRESHOLD 6.0f
#define LANDING_ALIGNMENT_THRESHOLD 0.7f

namespace physics {
bool check_surface_collision(const RigidBody &body);
void resolve_surface_collision(RigidBody &body);
Vec3 ship_down_direction(const world::Ship &ship);
void update_ship_collision_state(world::Ship &ship);
} // namespace physics

#endif
