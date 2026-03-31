#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "custom_preset.h"

void material_gold();
void material_grey();
void material_dark_grey();
void material_red();
void material_white();
void material_black();
void test_light();
float textureRandom();
void PolyFaceCylindre(float hauteur, float rayon, int ns,
                         float randomTexture);
void PolyFaceConeCut(float hauteur, float rayon_A, float rayon_B, int ns);
void PolyFacePrism(int face, int total_face, float height, float length_A,
                   float length_B, int nbPolygon, bool closed,
                   bool randomTexture);
void PolyFaceSurface(float size_x, float size_y, int nbPolygon_x,
                     int nbPolygon_y, bool randomTexture);
float LEM_anim();
void LEM(void);
void keyboard(unsigned char key, int x, int y);
void special(int specialKey, int x, int y);
void mouse(int button, int state, int x, int y);
void mouseMotion(int x, int y);

static void set_lighting();
static void set_material();
static void set_display();
static void set_idle();