#include "collision.h"
#include "../input/input.h"
#include "../render/moon_model.h"
#include <cstdio>

namespace physics {

Vec3 get_local_position(const Vec3 position) {
  return position - MOON_POSITION;
}

bool check_surface_collision(const RigidBody &body) {
  if (get_moon_scene() != MOON_SCENE_SURFACE)
    return false;
  Vec3 local_pos = get_local_position(body.position);
  float ground = get_lunar_height(local_pos.x, local_pos.z);
  return body.position.y - body.radius <= ground;
}

void resolve_surface_collision(RigidBody &body) {
  float step = PATCH_SIZE / GRID_STEPS;

  Vec3 local_pos = get_local_position(body.position);
  float ground = get_lunar_height(local_pos.x, local_pos.z);

  body.position.y = ground + body.radius;

  float nx, ny, nz;
  compute_normal(local_pos.x, local_pos.z, step, nx, ny, nz);
  Vec3 normal(nx, ny, nz);

  float vdot = dot(body.velocity, normal);
  if (vdot < 0.0f) {
    body.velocity -= normal * vdot;
  }
}

Vec3 ship_down_direction(const world::Ship &ship) {
  Vec3 local_down(0.0f, -1.0f, 0.0f);
  Vec3 oriented = input::rotate_pitch(local_down, ship.rotation.x);
  oriented = input::rotate_yaw(oriented, ship.rotation.y);
  return normalize(oriented);
}

void update_ship_collision_state(world::Ship &ship) {
  if (ship.state == world::SHIP_LANDED || ship.state == world::SHIP_DESTORYED) {
    return;
  }

  RigidBody body;
  body.position = ship.position;
  body.velocity = ship.velocity;
  body.radius = ship.radius;

  if (!check_surface_collision(body)) {
    ship.state = world::SHIP_ROAMING;
    return;
  }

  float nx, ny, nz;
  Vec3 local_pos = get_local_position(body.position);
  compute_normal(local_pos.x, local_pos.z, 1.0f, nx, ny, nz);
  Vec3 terrain_normal(nx, ny, nz);

  Vec3 ship_down = ship_down_direction(ship);

  float landing_alignment = dot(ship_down, terrain_normal);
  float speed = length(ship.velocity);

  if (landing_alignment >= LANDING_ALIGNMENT_THRESHOLD) {
    ship.state = world::SHIP_LANDED;

    Vec3 ship_local = get_local_position(ship.position);
    float ground = get_lunar_height(ship_local.x, ship_local.z);
    ship.position.y = ground + ship.radius;

    ship.velocity = Vec3(0.0f, 0.0f, 0.0f);
    return;
  }

  if (speed > CRASH_SPEED_THRESHOLD) {
    ship.state = world::SHIP_DESTORYED;
    return;
  }

  resolve_surface_collision(body);
  ship.position = body.position;
  ship.velocity = body.velocity;

  ship.state = world::SHIP_ROAMING;
}
} // namespace physics