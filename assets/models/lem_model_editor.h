/* Modélisation d'un attérisseur spatial        */
/*                                              */
/* Projet Objectif Lune                         */

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "../../src/input/keyboard.h"
#include "../../src/render/renderer.h"
#include "../../src/input/input.h"
#include "lem.h"

void lem_model(void);
void lem_display(void);
void lem_idle(void);
void lem_keyboard(unsigned char key, int x, int y);
void lem_mouse(int button, int state, int x, int y);
void lem_mouse_motion(int x, int y);
void lem_passive_mouse_motion(int x, int y);