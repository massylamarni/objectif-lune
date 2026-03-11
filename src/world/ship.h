#ifndef WORLD_SHIP
#define WORLD_SHIP

#include "../math/vec3.h"
#include <cmath>

namespace world {
struct Ship {
  Vec3 position;
  Vec3 velocity;

  Vec3 rotation;

  float thrust_power;
  float mass;

  bool thrusting;
};

Ship create_ship(const Vec3 position);
void ship_update(Ship &ship, float dt);
void ship_apply_thrust(Ship &ship, float dt);
Vec3 ship_forward(const Ship &ship);
} // namespace world

#endif