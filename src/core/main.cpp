#include "game.h"
#include <GL/glut.h>

static bool running = true;

int main(int argc, char **argv) {
  render::init(&argc, argv);
  game_init(render::SCREEN_WIDTH, render::SCREEN_HEIGHT);

  glutMainLoop();

  return 0;
}