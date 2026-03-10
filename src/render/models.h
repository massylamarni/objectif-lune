#ifndef RENDER_MODELS
#define RENDER_MODELS

#include "../world/planet.h"
#include "../world/ship.h"
#include <GL/gl.h>
#include <GL/glu.h>

namespace render {
void draw_planet(const world::Planet &planet);
void draw_ship(const world::Ship &ship);
} // namespace render

#endif