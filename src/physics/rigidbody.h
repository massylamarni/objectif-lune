#ifndef PHYSICS_RIGIDBODY
#define PHYSICS_RIGIDBODY

#include "../math/vec3.h"

namespace physics {
struct RigidBody {
  int id;
  Vec3 position;
  Vec3 velocity;

  float mass;

  Vec3 accumulated_force;
};

RigidBody create_rigidbody(const Vec3 &position, float mass);
void rb_apply_force(RigidBody &body, const Vec3 &force);
void rb_clear_forces(RigidBody &body);
void rb_integrate(RigidBody &body, float dt);
} // namespace physics

#endif