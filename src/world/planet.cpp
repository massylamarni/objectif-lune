#include "planet.h"
#include "../render/moon_model.h"
#include <cstdio>

namespace world {
Planet create_planet(int id, const Vec3 position, float radius, float mass) {
  Planet p;
  p.id = id;
  p.position = position;
  p.radius = radius;
  p.mass = mass;
  return p;
}

float distance_to_surface(const Planet planet, const Vec3 point) {
  if (get_moon_scene() == MOON_SCENE_SURFACE) {
    float ox, oz;
    get_cached_origin(ox, oz);

    float terrain_h = get_interpolated_height(point.x, point.z, ox, oz);
    return point.y - terrain_h;
  }
  float center_distance = length(point - planet.position);
  return center_distance - planet.radius;
}
} // namespace world