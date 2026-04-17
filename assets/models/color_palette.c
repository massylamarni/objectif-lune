#include "color_palette.h"

float tmp_color[] = {0.0F, 0.0F, 0.0F, 1.0F}; // Made

float black[] = {0.0F, 0.0F, 0.0F, 1.0F};

float dark_grey[] = {0.2F, 0.2F, 0.2F, 1.0F};

float grey[] = {0.5F, 0.5F, 0.5F, 1.0F};

float light_grey[] = {0.8F, 0.8F, 0.8F, 1.0F};

float gold[] = {0.9F, 0.6F, 0.1F, 1.0F};

float red[] = {1.0F, 0.0F, 0.0F, 1.0F};

float red_boost[] = {2.0F, 1.25F, 1.25F, 1.0F}; // Made for ligth

float green[] = {0.0F, 1.0F, 0.0F, 1.0F};

float blue[] = {0.0F, 0.0F, 1.0F, 1.0F};

float rose[] = {1.0F, 0.9F, 0.9F, 1.0F};

float yellow[] = {1.0F, 0.5F, 0.3F, 1.0F};

float white[] = {1.0F, 1.0F, 1.0F, 1.0F};

float ambient[] = {0.5f, 0.5f, 0.5f, 1.0f};

void material_gold() {
  // printf ("Material GOLD\n");

  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, gold);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, grey);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, black);
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 120.0F);

  glColor4fv(gold);
}

void material_grey() {
  // printf ("Material GREY\n");

  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, grey);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, dark_grey);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, black);
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100.0F);

  glColor4fv(grey);
}

void material_dark_grey() {
  // printf ("Material DARK GREY\n");

  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, dark_grey);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, grey);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, black);
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 70.0F);

  glColor4fv(dark_grey);
}

void material_light_grey() {
  // printf ("Material LIGHT GREY\n");

  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, light_grey);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, dark_grey);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, black);
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20.0F);

  glColor4fv(light_grey);
}

void material_red() {
  // printf ("Material RED\n");

  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, red);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, rose);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, black);
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100.0F);

  glColor4fv(red);
}

void material_white() {
  // printf ("Material WHITE\n");

  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, black);
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50.0F);

  glColor4fv(white);
}

void material_flame() {
  // printf ("Material FLAME\n");

  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, black);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, black);
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, yellow);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50.0F);

  glColor4fv(white);
}

void material_black() {
  // printf ("Material BLACK\n");
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, black);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, black);
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100.0F);

  glColor4fv(black);
}

void material_sun() {

  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, black);
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, white);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100.0F);

  glColor4fv(white);
}

void colorCoeff(float base[], float coeff) { // Set tmp_color to another color
  tmp_color[0] = base[0] * coeff;
  tmp_color[1] = base[1] * coeff;
  tmp_color[2] = base[2] * coeff;
  tmp_color[3] = base[3] * coeff;
}
