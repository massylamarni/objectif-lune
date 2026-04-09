#include "ship.h"
#include "world.h"

namespace world {
Ship create_ship(const Vec3 position) {
  Ship ship;

  ship.position = position;
  ship.velocity = Vec3(0, 0, 0);
  ship.rotation = Vec3(0, 0, 0);

  ship.thrust_power = SHIP_THRUST_POWER;
  ship.mass = SHIP_MASS;
  ship.radius = SHIP_RADIUS;

  ship.thrusting = false;

  return ship;
}

void ship_update(Ship &ship, float dt) {
  if (ship.thrusting)
    ship_apply_thrust(ship, dt);

  ship.position += ship.velocity * dt;
}

void ship_apply_thrust(Ship &ship, float dt) {
  Vec3 forward = ship_forward(ship);

  ship.velocity += forward * ship.thrust_power * dt;
}

Vec3 ship_forward(const Ship &ship) {
  float yaw = ship.rotation.y;

  float x = sin(yaw);
  float z = -cos(yaw);

  return normalize(Vec3(x, 0, z));
}
} // namespace world