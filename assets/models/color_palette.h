#ifndef COLOR_PALETTE
#define COLOR_PALETTE

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

extern float tmp_color[];
extern float black[];
extern float dark_grey[];
extern float grey[];
extern float light_grey[];
extern float gold[];
extern float red[];
extern float red_boost[];
extern float green[];
extern float blue[];
extern float rose[];
extern float yellow[];
extern float white[];
extern float ambient[];

void material_gold();

void material_grey();

void material_dark_grey();

void material_light_grey();

void material_red();

void material_white();

void material_flame();

void material_black();

void material_sun();

void colorCoeff(float base[], float coeff);

#endif
