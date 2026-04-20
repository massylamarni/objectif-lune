#ifndef RENDER_MODELS
#define RENDER_MODELS

#include "../math/vec3.h"
#include "../world/planet.h"
#include "../world/ship.h"
#include "../../assets/models/explosion.h"
#include "../../assets/models/lem.h"
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "textures.h"

namespace render {
void draw_planet(const world::Planet &planet);
void draw_moon(const world::Planet &moon, const Vec3 &ship_position);
void draw_ship(const world::Ship &ship);
void draw_mini_ship(const world::Ship &ship);
void draw_lem();
void draw_explosion(const world::Ship &ship);
} // namespace render

#endif
