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

void init_lem (unsigned int texture_id);

void reactor_init (bool primary_reactor, float general_animation) ;

void reactor_idle (bool primary_reactor, float general_animation);

float lem_anim (bool win_value, float general_animation, float anim_win_offset);

void reactor_anim (float power, bool primary_reactor, float general_animation);

void rotation_module (float rotation_direction, float rotation_power, float general_animation, int nbPolygon);

void lem (bool reactor_activity, float rotation_direction, float rotation_power, float anim_win_offset, bool win_value, float general_animation, int nbPolygon);

void rotation_update (int x, int y, int prst_wTx, int prst_wTy, float* rotation_direction, float* rotation_power);
