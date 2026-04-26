#include "start.h"
#include <GL/glut.h>

int main(int argc, char **argv) {
  render::init(&argc, argv);
  start_init();

  glutMainLoop();

  return 0;
}
