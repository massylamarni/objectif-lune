 /* Modélisation d'un attérisseur spatial        */ 
 /*                                              */ 
 /* Projet Objectif Lune                         */ 

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "color_palette.h"
#include "polyface_object.h"

#include "lem.h"

 /* Variables globales                           */

 /* Fonction d'initialisation des paramètres     */
 /* OpenGL ne changeant pas ou peu au cours de   */
 /* la vie du programme                          */

void load_moon (void) {
  
}

 /* Dessin de la Scène                           */


/* MÉMO
  for (int i = 0 ; i < XXX ; i++) {}
  glPushMatrix ();
  glPopMatrix ();
  
  glRotatef (90.0F, 0.0F, 0.0F, 0.0F);
  glTranslatef (0.0F, 0.0F, 0.0F);
  glScalef (0.0F, 0.0F, 0.0F);
  
  glColor3f (1.0F, 1.0F, 1.0F);
  
  glVertex3f (1.0F, 1.0F, 1.0F);
  glNormal3f (1.0F, 0.0F, 0.0F);
  
  glutSolidSphere (0.5, 16, 16);
*/

void moon_sphere (int nbPolygon) {
  
}

