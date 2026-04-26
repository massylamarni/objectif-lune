#include "ship.h"
#include "../input/input.h"
#include "world.h"

namespace world {
Ship create_ship(const Vec3 position) {
  Ship ship;
  ship.position = position;
  ship.velocity = Vec3(0, 0, 0);
  ship.rotation = Vec3(0, 0, 0);
  ship.angular_velocity = Vec3(0, 0, 0);

  ship.thrust_power = SHIP_THRUST_POWER;
  ship.mass = SHIP_MASS;
  ship.radius = SHIP_RADIUS;

  ship.thrusting = false;
  ship.state = SHIP_ROAMING;

  return ship;
}

void ship_update(Ship &ship, float dt) {
  ship.rotation += ship.angular_velocity * dt;

  if (ship.thrusting)
    ship_apply_thrust(ship, dt);

  ship.position += ship.velocity * dt;

  float speed = length(ship.velocity);
  if (speed > SHIP_MAX_SPEED) {
    ship.velocity = normalize(ship.velocity) * SHIP_MAX_SPEED;
  }
}

void ship_apply_thrust(Ship &ship, float dt) {
  Vec3 up = Vec3(0, 1, 0);
  up = input::rotate_pitch(up, ship.rotation.x);
  up = input::rotate_yaw(up, ship.rotation.y);

  float accel = ship.thrust_power / ship.mass;
  ship.velocity += up * accel * dt;
}

Vec3 ship_forward(const Ship &ship) {
  float yaw = ship.rotation.y;

  float x = sin(yaw);
  float z = -cos(yaw);

  return normalize(Vec3(x, 0, z));
}
} // namespace world