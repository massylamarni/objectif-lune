#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>


void fummee_idle ();

void fummee_anim (float power);

static float resteDivf(float dividende, float diviseur);

static void ExplosionSphere(int nb_frag, float rayon_int, float rayon_ext);

void ExplosionModel(void);

void startExplosionAnimation ();

void idle2 (float animation_time);

void idle1 (float animation_time);

void explosion_idle (float animation_time);
