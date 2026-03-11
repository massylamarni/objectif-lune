#include "planet.h"
#include <cstdio>

namespace world {
Planet create_planet(int id, const Vec3 position, float radius, float gravity) {
  Planet p;
  p.id = id;
  p.position = position;
  p.radius = radius;
  p.gravity = gravity;
  return p;
}

float distance_to_surface(const Planet planet, const Vec3 point) {
  float center_distance = length(point - planet.position);
  return center_distance - planet.radius;
}
} // namespace world