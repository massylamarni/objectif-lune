#ifndef CORE_GAME
#define CORE_GAME

#include "../input/input.h"
#include "../physics/collision.h"
#include "../physics/gravity.h"
#include "../render/camera.h"
#include "../render/models.h"
#include "../render/renderer.h"
#include "../world/planet.h"
#include "../world/ship.h"
#include "../world/world.h"
#include "time.h"

struct GameState {
  world::Planet earth;
  world::Planet moon;
  world::Ship ship;
  render::Camera camera;
};

void game_init(int width, int height);
void game_update(float dt);
void game_render();

#endif