#include "rigidbody.h"

namespace physics {
RigidBody create_rigidbody(const Vec3 &position, float mass) {
  RigidBody body;
  body.position = position;
  body.velocity = Vec3(0, 0, 0);
  body.mass = mass;
  body.accumulated_force = Vec3(0, 0, 0);
  return body;
}

void rb_apply_force(RigidBody &body, const Vec3 &force) {
  body.accumulated_force += force;
}

void rb_clear_forces(RigidBody &body) {
  body.accumulated_force = Vec3(0, 0, 0);
}

void rb_integrate(RigidBody &body, float dt) {
  Vec3 acceleration = body.accumulated_force / body.mass;
  body.velocity += acceleration * dt;
  body.position += body.velocity * dt;

  LOGD("%s now has acceleration: (x: %f, y: %f, z: %f), dt is: %f",
       ID_MAPPING[body.id], acceleration.x, acceleration.y, acceleration.z, dt);
  rb_clear_forces(body);
}
} // namespace physics