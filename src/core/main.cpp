#include "game.h"
#include <GL/glut.h>

int main(int argc, char **argv) {
  render::init(&argc, argv);
  game_init();

  glutMainLoop();

  return 0;
}