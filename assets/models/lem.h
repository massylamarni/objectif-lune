/* Configuration par défault de variable OpenGL */ 
/*                                              */ 
/* Projet Objectif Lune                         */ 

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "color_palette.h"
#include "polyface_object.h"

 /* Fonction d'initialisation des paramètres     */ 
 /* OpenGL ne changeant pas ou peu au cours de   */ 
 /* la vie du programme                          */ 

void init_lem (void);

void reactor_init (float anim_reactor_offset [], float general_animation) ;

void reactor_idle (float anim_reactor_offset [], float general_animation);

float lem_anim (bool win_value, float general_animation, float anim_win_offset);

void reactor_anim (float power, float anim_reactor_offset [], float general_animation);

void rotation_module (float rotation_direction, float rotation_power, float anim_reactor_offset [], float general_animation, int nbPolygon);

void lem (bool reactor_activity, float rotation_direction, float rotation_power, float anim_win_offset, float anim_reactor_offset [], bool win_value, float general_animation, int nbPolygon);

void rotation_update (int x, int y, int prst_wTx, int prst_wTy, float* rotation_direction, float* rotation_power);
