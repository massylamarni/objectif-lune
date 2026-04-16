#include "../world/planet.h"
#include "../world/world.h"
#include "../../assets/models/color_palette.h"
#include <GL/gl.h>
#include <cmath>

#define MOON_TERRAIN_SIZE 250
#define MOON_TERRAIN_SCALE 5.0f
#define MOON_LOD_DISTANCE 300.0f
#define TERRAIN_FADE_START 300.0f
#define TERRAIN_FADE_END 200.0f
#define MOON_HEIGHT_BIAS 10.0f

void draw_moon_sphere(const world::Planet &planet);
void draw_moon_terrain(const world::Planet &moon, const Vec3 &ship_position,
                       float t);