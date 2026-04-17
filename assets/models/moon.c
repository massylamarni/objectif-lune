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
  material_light_grey ();
  
  //glutSolidSphere (1.0, nbPolygon, nbPolygon);
  
  float w_pos = 0.0F; // w_=> x + z position
  float x_pos = 0.0F;
  float y_pos = -1.0F;
  float z_pos = 0.0F;
  float tex_offset = (float) 1.0F / nbPolygon;
  
  for (int i = 0 ; i < nbPolygon ; i++) {
    glBegin (GL_QUAD_STRIP);
    for (int j = 0 ; j < nbPolygon ; j++) {
      w_pos = sin ((float) i / nbPolygon * M_PI); // sin
      y_pos = -cos ((float) i / nbPolygon * M_PI); // -cos
      x_pos = w_pos * cos ((float) j / nbPolygon * M_PI * 2); // cos
      z_pos = w_pos * sin ((float) j / nbPolygon * M_PI * 2); // sin
      glNormal3f (x_pos, y_pos, z_pos);
      glTexCoord2f ((float) j / nbPolygon, (float) i / nbPolygon);
      glVertex3f (x_pos, y_pos, z_pos);
      
      w_pos = sin ((float) (i + 1) / nbPolygon * M_PI); // sin
      y_pos = -cos ((float) (i + 1) / nbPolygon * M_PI); // -cos
      x_pos = w_pos * cos ((float) j / nbPolygon * M_PI * 2); // cos
      z_pos = w_pos * sin ((float) j / nbPolygon * M_PI * 2); // sin
      glNormal3f (x_pos, y_pos, z_pos);
      glTexCoord2f ((float) j / nbPolygon, (float) i / nbPolygon + tex_offset);
      glVertex3f (x_pos, y_pos, z_pos);
      
      w_pos = sin ((float) i / nbPolygon * M_PI); // sin
      y_pos = -cos ((float) i / nbPolygon * M_PI); // -cos
      x_pos = w_pos * cos ((float) (j + 1) / nbPolygon * M_PI * 2); // cos
      z_pos = w_pos * sin ((float) (j + 1) / nbPolygon * M_PI * 2); // sin
      glNormal3f (x_pos, y_pos, z_pos);
      glTexCoord2f ((float) j / nbPolygon + tex_offset, (float) i / nbPolygon);
      glVertex3f (x_pos, y_pos, z_pos);
      
      w_pos = sin ((float) (i + 1) / nbPolygon * M_PI); // sin
      y_pos = -cos ((float) (i + 1) / nbPolygon * M_PI); // -cos
      x_pos = w_pos * cos ((float) (j + 1) / nbPolygon * M_PI * 2); // cos
      z_pos = w_pos * sin ((float) (j + 1) / nbPolygon * M_PI * 2); // sin
      glNormal3f (x_pos, y_pos, z_pos);
      glTexCoord2f ((float) j / nbPolygon + tex_offset, (float) i / nbPolygon + tex_offset);
      glVertex3f (x_pos, y_pos, z_pos);
      //printf ("%f, %f, %f\n", x_pos, y_pos, z_pos);
    }
    glEnd ();
  }
}

