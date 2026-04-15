#include "collision.h"
#include "../input/input.h"

namespace physics {
bool check_planet_collision(const RigidBody &body,
                            const world::Planet &planet) {
  Vec3 diff = body.position - planet.position;
  float dist = length(diff);
  return dist <= planet.radius + body.radius;
}

void resolve_planet_collision(RigidBody &body, const world::Planet &planet) {
  Vec3 normal = normalize(body.position - planet.position);
  body.position = planet.position + normal * (planet.radius + body.radius);
  float velocity_normal = dot(body.velocity, normal);
  if (velocity_normal < 0.0f) {
    body.velocity -= normal * velocity_normal;
  }
}

Vec3 ship_down_direction(const world::Ship &ship) {
  Vec3 local_down(0.0f, -1.0f, 0.0f);
  Vec3 oriented = input::rotate_pitch(local_down, ship.rotation.x);
  oriented = input::rotate_yaw(oriented, ship.rotation.y);
  return normalize(oriented);
}

void update_ship_collision_state(world::Ship &ship,
                                 const world::Planet &planet) {
  if (ship.state == world::SHIP_LANDED || ship.state == world::SHIP_DESTORYED) {
    return;
  }

  RigidBody body;
  body.position = ship.position;
  body.radius = ship.radius;

  if (!check_planet_collision(body, planet)) {
    ship.state = world::ship_state::SHIP_ROAMING;
    return;
  }

  Vec3 to_planet = normalize(planet.position - ship.position);
  Vec3 ship_down = ship_down_direction(ship);
  float landing_alignment = dot(ship_down, to_planet);
  float speed = length(ship.velocity);

  if (landing_alignment >= LANDING_ALIGNMENT_THRESHOLD) {
    ship.state = world::ship_state::SHIP_LANDED;
    return;
  }

  if (speed > CRASH_SPEED_THRESHOLD) {
    ship.state = world::ship_state::SHIP_DESTORYED;
    return;
  }

  ship.state = world::ship_state::SHIP_ROAMING;
}
} // namespace physics