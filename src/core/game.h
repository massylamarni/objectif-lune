#ifndef CORE_GAME
#define CORE_GAME

#include "../input/input.h"
#include "../output/logs.h"
#include "../output/debug.h"
#include "../physics/collision.h"
#include "../physics/gravity.h"
#include "../render/camera.h"
#include "../render/models.h"
#include "../render/renderer.h"
#include "../render/utils.h"
#include "../ui/minimap.h"
#include "../world/planet.h"
#include "../world/ship.h"
#include "time.h"

struct GameState {
  world::Planet earth;
  world::Planet moon;
  world::Planet sun;
  world::Ship ship;
  render::Camera camera;
  bool player_won;
};

struct GameFps {
  int frame_count;
  float fps_time_accumulator;
  float fps;
};

void game_init(int width, int height);
void game_update();
void game_update_callback();
void game_update_hook();
void game_display();
void game_display_callback();
void game_display_hook();
void update_fps_counter(float dt);

#endif