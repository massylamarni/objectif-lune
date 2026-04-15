#ifndef WORLD_SHIP
#define WORLD_SHIP

#include "../math/vec3.h"
#include <cmath>

namespace world {

typedef enum {
  SHIP_ROAMING,
  SHIP_LANDED,
  SHIP_DESTORYED
} ship_state;

struct Ship {
  Vec3 position;
  Vec3 velocity;

  Vec3 rotation;

  float thrust_power;
  float mass;
  float radius;

  bool thrusting;
  ship_state state;
};

Ship create_ship(const Vec3 position);
void ship_update(Ship &ship, float dt);
void ship_apply_thrust(Ship &ship, float dt);
Vec3 ship_forward(const Ship &ship);
} // namespace world

#endif