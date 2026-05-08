#ifndef RENDER_MODELS
#define RENDER_MODELS

#include "../world/planet.h"
#include "../world/ship.h"
#include "../math/vec3.h"
#include "../input/input.h"
#include "../../assets/models/explosion.h"
//#include "../../assets/models/lem.h"
#include "moon_model.h"
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "textures.h"

namespace render {
void draw_planet(const world::Planet &planet, Vec3 *ship_position = nullptr);
void draw_skybox(float radius, Vec3 *ship_position);
void idle_ship (float dt, float win_v, bool thrusting, float rotation_power_v);
void draw_ship(const world::Ship &ship);
void draw_mini_ship(const world::Ship &ship);
void draw_explosion(const world::Ship &ship);
} // namespace render

#endif
