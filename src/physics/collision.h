#ifndef PHYSICS_COLLISION
#define PHYSICS_COLLISION

#include "../world/planet.h"
#include "../world/ship.h"
#include "rigidbody.h"

#define CRASH_SPEED_THRESHOLD 6.0f
#define LANDING_ALIGNMENT_THRESHOLD 0.7f

namespace physics {
bool check_planet_collision(const RigidBody &body, const world::Planet &planet);
world::ship_state check_ship_planet_collision(const world::Ship &ship,
                                              const world::Planet &planet);
void resolve_planet_collision(RigidBody &body, const world::Planet &planet);
void update_ship_collision_state(world::Ship &ship,
                                 const world::Planet &planet);
Vec3 ship_down_direction(const world::Ship &ship);
} // namespace physics

#endif
