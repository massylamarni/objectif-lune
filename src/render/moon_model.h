#include "../../assets/models/color_palette.h"
#include "../world/planet.h"
#include "../world/world.h"
#include <GL/gl.h>
#include <cmath>

#include "../physics/collision.h"
#include <vector>

#define MOON_TERRAIN_SIZE 250
#define MOON_TERRAIN_SCALE 5.0f
#define MOON_LOD_DISTANCE 300.0f
#define TERRAIN_FADE_START 300.0f
#define TERRAIN_FADE_END 200.0f
#define MOON_HEIGHT_BIAS 10.0f

namespace models {
void draw_moon_sphere(const world::Planet &planet);
void draw_moon_terrain(const world::Planet &moon, const Vec3 &ship_position,
                       float t);
bool check_moon_collision(const world::Planet &moon, const Vec3 &ship_position,
                          const Vec3 &target_position, float t);


bool check_planet_collision(const physics::RigidBody &body,
                            const world::Planet &planet, const Vec3 &ship_pos,
                            float t);

void resolve_planet_collision(physics::RigidBody &body,
                              const world::Planet &planet, const Vec3 &ship_pos,
                              float t);
}