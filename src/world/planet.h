#ifndef WORLD_PLANET
#define WORLD_PLANET

#include "../math/vec3.h"
#include <cmath>

namespace world {
struct Planet {
  int id;
  Vec3 position;
  float radius;
  float gravity;
};

Planet create_planet(int id, const Vec3 position, float radius, float gravity);
float distance_to_surface(const Planet planet, const Vec3 point);
} // namespace world

#endif