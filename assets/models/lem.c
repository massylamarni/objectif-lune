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

 /* Variables globales */

float anim_reactor_offset [] = { -80.0F, -80.0F, -80.0F, -80.0F, -80.0F, -80.0F, -80.0F, -80.0F, -80.0F, -80.0F }; // Offset des blobs de fumée - réacteur ventral
float anim_rotation_offset [] = { 0.0F, 10.0F, 20.0F, 30.0F, 40.0F, 50.0F, 60.0F, 70.0F, 80.0F, 90.0F }; // Offset des blobs de fumée - réacteur de rotation

unsigned int texture_lem_id; // Index de la texture à appliquer
float reactor_light_inertia = 0.0F; // Coefficient d'inertie de la puissance de la lumière ventrale

void init_lem (unsigned int texture_id) { // Réglage des lumière 2, 3 et 4, et sauvegarde de l'index de la texture
  texture_lem_id = texture_id;
  
  glLightf  (GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.0F);
  glLightf  (GL_LIGHT2, GL_LINEAR_ATTENUATION, 1.0F);
  glLightf  (GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 1.0F);
  
  glLightf  (GL_LIGHT3, GL_CONSTANT_ATTENUATION, 0.0F);
  glLightf  (GL_LIGHT3, GL_LINEAR_ATTENUATION, 1.0F);
  glLightf  (GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 1.0F);
  
  glLightf  (GL_LIGHT4, GL_CONSTANT_ATTENUATION, 0.0F);
  glLightf  (GL_LIGHT4, GL_LINEAR_ATTENUATION, 1.0F);
  glLightf  (GL_LIGHT4, GL_QUADRATIC_ATTENUATION, 1.0F);
  
  glEnable (GL_LIGHT2);
  glEnable (GL_LIGHT3);
  glEnable (GL_LIGHT4);
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

void reactor_init (bool primary_reactor, float general_animation) { // Repositionnement des blobs de fumée
  if (primary_reactor) {
    for (int i = 0 ; i < 10 ; i++) {
      anim_reactor_offset [i] = general_animation + (i * 10.0F);
    }
  }
  else {
    for (int i = 0 ; i < 10 ; i++) {
      anim_rotation_offset [i] = general_animation + (i * 10.0F);
    }
  }
}


void reactor_idle (bool primary_reactor, float general_animation) { // Mise à jour des blobs de fumée
  if (primary_reactor) {
    for (int i = 0 ; i < 10 ; i++) {
      if (general_animation - anim_reactor_offset [i] > 75) {
        anim_reactor_offset [i] = general_animation;
      }
    }
  }
  else {
    for (int i = 0 ; i < 10 ; i++) {
      if (general_animation - anim_rotation_offset [i] > 75) {
        anim_rotation_offset [i] = general_animation;
      }
    }
  }
}

float lem_anim (bool win_value, float general_animation, float anim_win_offset) {
  if (win_value) {
    if (general_animation - anim_win_offset > 100) {
      return -60.0F;
    }
    return (general_animation - anim_win_offset) * -1.8F + 120.0F;
  }
  else {
    return 120.0F;
  }
}

void reactor_anim (float power, bool primary_reactor, float general_animation) { /* [0.0F - 1.0F]*/
  material_flame ();
  float (* anim_offset) [] = &anim_reactor_offset;
  if (!primary_reactor) anim_offset = &anim_rotation_offset;
  
  if (0.15F < power) {
    glPushMatrix ();
    if (power > 1.0F) power = 1.0F;
    glScalef (power, power, power);
    for (int i = 0 ; i < 10 ; i++) {
      if (general_animation - (*anim_offset) [i] < power * 75 && general_animation - (*anim_offset) [i] >= 0) {
        
        glPushMatrix ();
         
        glRotatef ((i * 108.0F), 0.0F, 1.0F, 0.0F);
        glTranslatef (0.005F * (general_animation - (*anim_offset) [i]), -0.01F * (general_animation - (*anim_offset) [i]), (float) i * 0.01F);
        glutSolidSphere (0.0025F * ((*anim_offset) [i] - general_animation + 75), 3 + i, 13 - i);
        
        glPopMatrix ();
      }
    }
      glPopMatrix ();
  }
}

void rotation_module (float rotation_direction, float rotation_power, float general_animation, int nbPolygon) {
  glPushMatrix ();
  
  for (int i = 0 ; i < 4 ; i++) {
    glPushMatrix ();
    material_dark_grey (); // Mini-Tuyère
    glRotatef (90.0F * i, 1.0F, 0.0F, 0.0F);
    glTranslatef (0.0F, 0.125F, 0.0F);
    PolyFaceConeCut (0.125F, 0.1F, 0.125F, nbPolygon, 3);
    glRotatef (180.0F, 1.0F, 0.0F, 0.0F);
    glTranslatef (0.0F, -0.025F, 0.0F);
    PolyFaceConeCut (-0.05F, 0.0F, -0.1F, nbPolygon, 3);
    glTranslatef (0.0F, -0.05F, 0.0F);
    PolyFaceConeCut (-0.05F, -0.1F, -0.125F, nbPolygon, 3);
    glScalef (0.2F, 0.35F, 0.2F);
    reactor_anim (4.0F * rotation_power * cos ((90.0F + 90.0F * i + rotation_direction) / 180.0 * M_PI), false, general_animation); // Flamme
    glPopMatrix ();
  }
  
  material_grey (); // Support
  glPushMatrix ();
  glScalef (1.2F, 1.0F, 1.0F);
  PolyFaceCube (0.25F, 3, 2);
  
  glPopMatrix ();
  
  glPopMatrix ();
}

void lem (bool reactor_activity, float rotation_direction, float rotation_power, float anim_win_offset, bool win_value, float general_animation, int nbPolygon) {
  glBindTexture(GL_TEXTURE_2D, texture_lem_id);
  glPushMatrix ();
  
  glPushMatrix (); // Lumière Ventrale
  glTranslatef (0.0F, -0.5F, 0.0F);
  glLightfv (GL_LIGHT2, GL_POSITION, black);
  float coeff_ventral = (0.9F + 0.1F * cos (general_animation / 5)) * reactor_light_inertia;
  if (reactor_activity) {
    reactor_light_inertia += 0.05F;
    if (reactor_light_inertia >= 1.0F) reactor_light_inertia = 1.0F;
  }
  else {
    reactor_light_inertia -= 0.025F;
    if (reactor_light_inertia <= 0.0F) reactor_light_inertia = 0.0F;
  }
  coeff_ventral *= reactor_light_inertia;
  colorCoeff (red_boost, coeff_ventral);
  glLightfv (GL_LIGHT2, GL_DIFFUSE,  tmp_color);
  colorCoeff (gold, coeff_ventral);
  glLightfv (GL_LIGHT2, GL_SPECULAR, tmp_color);
  colorCoeff (white, coeff_ventral);
  glLightfv (GL_LIGHT2, GL_AMBIENT,  tmp_color);
  glPopMatrix ();
  
  glPushMatrix (); // Lumière Babord
  glTranslatef (1.1F, 1.2F, 0.0F);
  glRotatef (-85.0F, 0.0F, 0.0F, 1.0F);
  glRotatef (-rotation_direction, 0.0F, 1.0F, 0.0F);
  glTranslatef (0.2F, 0.0F, 0.0F);
  glLightfv (GL_LIGHT3, GL_POSITION, black);
  float coeff_babord = (0.25F + 0.05F * cos (general_animation / 5.5)) * rotation_power;
  colorCoeff (red_boost, coeff_babord);
  glLightfv (GL_LIGHT3, GL_DIFFUSE,  tmp_color);
  colorCoeff (gold, coeff_babord);
  glLightfv (GL_LIGHT3, GL_SPECULAR, tmp_color);
  colorCoeff (white, coeff_babord);
  glLightfv (GL_LIGHT3, GL_AMBIENT,  tmp_color);
  glPopMatrix ();
  
  glPushMatrix (); // Lumière Tribord
  glTranslatef (-1.1F, 1.2F, 0.0F);
  glRotatef (85.0F, 0.0F, 0.0F, 1.0F);
  glRotatef (rotation_direction, 0.0F, 1.0F, 0.0F);
  glTranslatef (0.2F, 0.0F, 0.0F);
  glLightfv (GL_LIGHT4, GL_POSITION, black);
  float coeff_tribord = (0.25F + 0.05F * cos (general_animation / 5.9)) * rotation_power;
  colorCoeff (red_boost, coeff_tribord);
  glLightfv (GL_LIGHT4, GL_DIFFUSE,  tmp_color);
  colorCoeff (gold, coeff_tribord);
  glLightfv (GL_LIGHT4, GL_SPECULAR, tmp_color);
  colorCoeff (white, coeff_tribord);
  glLightfv (GL_LIGHT4, GL_AMBIENT,  tmp_color);
  glPopMatrix ();
  
  glRotatef (-22.5F, 0.0F, 1.0F, 0.0F);
  
  material_gold ();
  PolyFacePrism (8, 8, 1.0F, 1.0823922F, 1.0823922F, nbPolygon, true, 1, true); // Corps
  // 1.0823922F == 1 / cos (22.5 * 2 * M_PI / 360) ou le rayon du cercle inscrit d'un octogone de cercle circonscris de 1
  
  glRotatef (22.5F, 0.0F, 1.0F, 0.0F);
  for (int i = 0 ; i < 4 ; i++) { // Pieds
    glPushMatrix ();
    glRotatef (i * 90.0F, 0.0F, 1.0F, 0.0F);
    glTranslatef (1.3F, 0.15F, 0.0F);
    PolyFaceCylindre (0.5F, 0.05F, nbPolygon, 4, true);
    
    glPushMatrix ();
    glRotatef (105.0F, 0.0F, 0.0F, 1.0F);
    PolyFaceCylindre (0.35F, 0.05F, nbPolygon, 4, true);
    glPopMatrix ();
    
    {
      glPushMatrix ();
      glTranslatef (0.0F, 0.5F, 0.0F);
      
      glPushMatrix ();
      
      glutSolidSphere (0.05, nbPolygon / 2, nbPolygon / 2);
      PolyFaceCube (0.1, 1, 4);
      
      glRotatef (50.0F, 0.0F, 0.0F, 1.0F);
      PolyFaceCylindre (0.45F, 0.05F, nbPolygon, 4, true);
      glPopMatrix ();
      
      glRotatef (-150.0F, 0.0F, 0.0F, 1.0F);
      PolyFaceCylindre (1.0F, 0.05F, nbPolygon, 4, true);
      
      glPopMatrix ();
    }
    
    glRotatef (-125.0F, 0.0F, 0.0F, 1.0F);
    PolyFaceCylindre (0.6F, 0.05F, nbPolygon, 1, true);
    
    glTranslatef (0.0F, 0.6F, 0.0F);
    glRotatef (-35.0F, 0.0F, 0.0F, 1.0F);
    PolyFaceCylindre (0.2F, 0.05F, nbPolygon, 1, true);
    
    glTranslatef (0.0F, 0.175F, 0.0F);
    glRotatef (-20.0F, 0.0F, 0.0F, 1.0F);
    PolyFacePrism (8, 8, 0.05F, 0.2F, 0.17F, nbPolygon / 2, true, 1, true);
    
    glPopMatrix ();
  }
  
  material_grey ();
  
  glPushMatrix (); // Tête
  
  glTranslatef (0.0F, 1.0F, 1.0F);
  glRotatef (-90.0F, 1.0F, 0.0F, 0.0F);
  PolyFacePrism (8, 16, 0.5F,  0.2F, 0.6F, nbPolygon / 2, true, 2, false);
  glTranslatef (0.0F, 0.5F, 0.0F);
  PolyFacePrism (8, 16, 0.25F, 0.6F, 1.0F, nbPolygon / 2, false, 2, false);
  glTranslatef (0.0F, 0.25F, 0.0F);
  PolyFacePrism (8, 16, 0.5F,  1.0F, 1.0F, nbPolygon / 2, false, 2, false);
  {
    glPushMatrix ();
    glRotatef (-10.0F, 0.0F, 1.0F, 0.0F);
    glTranslatef (1.125F, 0.25F, 0.0F);
    rotation_module (rotation_direction, rotation_power, general_animation, nbPolygon);
    glPopMatrix ();
    glPushMatrix ();
    glRotatef (-170.0F, 0.0F, 1.0F, 0.0F);
    glTranslatef (1.125F, 0.25F, 0.0F);
    glRotatef (180.0F, 0.0F, 0.0F, 1.0F);
    rotation_module (rotation_direction, rotation_power, general_animation, nbPolygon);
    glPopMatrix ();
  }
  glTranslatef (0.0F, 0.5F, 0.0F);
  PolyFacePrism (8, 16, 0.25F, 1.0F, 0.6F, nbPolygon / 2, true, 2, false);
  glTranslatef (0.0F, 0.25F, 0.0F);
  
  glPushMatrix ();
  glTranslatef (0.0F, 0.125F, 0.3F);
  PolyFaceSurface (0.8F, 0.25F, nbPolygon, nbPolygon / 2, 2, false);
  glPopMatrix ();
  glPushMatrix ();
  glTranslatef (0.0F, 0.375F, 0.3F);
  PolyFaceSurface (0.4F, 0.25F, nbPolygon / 2, nbPolygon / 2, 2, false);
  glPopMatrix ();
  glPushMatrix ();
  glTranslatef (0.0F, 0.5F, 0.15F);
  glRotatef (-90.0F, 1.0F, 0.0F, 0.0F);
  PolyFaceSurface (0.4F, 0.3F, nbPolygon / 2, nbPolygon / 2, 2, false);
  glPopMatrix ();
  glPushMatrix ();
  glTranslatef (0.0F, 0.25F, 0.15F);
  glRotatef (-90.0F, 1.0F, 0.0F, 0.0F);
  PolyFaceSurface (0.8F, 0.3F, nbPolygon, nbPolygon / 2, 2, false);
  glPopMatrix ();
  glPushMatrix ();
  glTranslatef (0.4F, 0.125F, 0.15F);
  glRotatef (90.0F, 0.0F, 1.0F, 0.0F);
  PolyFaceSurface (0.3F, 0.25F, nbPolygon / 2, nbPolygon / 2, 2, false);
  glPopMatrix ();
  glPushMatrix ();
  glTranslatef (-0.4F, 0.125F, 0.15F);
  glRotatef (-90.0F, 0.0F, 1.0F, 0.0F);
  PolyFaceSurface (0.3F, 0.25F, nbPolygon / 2, nbPolygon / 2, 2, false);
  glPopMatrix ();
  glPushMatrix ();
  glTranslatef (0.2F, 0.375F, 0.15F);
  glRotatef (90.0F, 0.0F, 1.0F, 0.0F);
  PolyFaceSurface (0.3F, 0.25F, nbPolygon / 2, nbPolygon / 2, 2, false);
  glPopMatrix ();
  glPushMatrix ();
  glTranslatef (-0.2F, 0.375F, 0.15F);
  glRotatef (-90.0F, 0.0F, 1.0F, 0.0F);
  PolyFaceSurface (0.3F, 0.25F, nbPolygon / 2, nbPolygon / 2, 2, false);
  glPopMatrix ();
  
  glPushMatrix ();
  glTranslatef (0.0F, 0.125F, 0.3F + tan (30.0 * 2 * M_PI / 360) / 8);
  glRotatef (-30.0F, 1.0F, 0.0F, 0.0F);
  PolyFaceSurface (0.4F, 1.0F / (cos (30.0 * 2 * M_PI / 360) * 4.0F), nbPolygon / 2, nbPolygon / 2, 2, false);
  glPushMatrix ();
  glTranslatef (0.2F, 0.0F, -0.15F);
  glRotatef (90.0F, 0.0F, 1.0F, 0.0F);
  PolyFaceSurface (0.3F, 1.0F / (cos (30.0 * 2 * M_PI / 360) * 4.0F), nbPolygon / 2, nbPolygon / 2, 2, false);
  glPopMatrix ();
  glPushMatrix ();
  glTranslatef (-0.2F, 0.0F, -0.15F);
  glRotatef (-90.0F, 0.0F, 1.0F, 0.0F);
  PolyFaceSurface (0.3F, 1.0F / (cos (30.0 * 2 * M_PI / 360) * 4.0F), nbPolygon / 2, nbPolygon / 2, 2, false);
  glPopMatrix ();
  glPopMatrix ();
  
  glPopMatrix ();
  
  glPushMatrix ();
  material_dark_grey (); // Tuyère
  glRotatef (180.0F, 1.0F, 0.0F, 0.0F);
  PolyFaceConeCut (0.3F, 0.3F, 0.4F, nbPolygon, 3);
  glRotatef (180.0F, 1.0F, 0.0F, 0.0F);
  PolyFaceConeCut (-0.1F, 0.0F, -0.2F, nbPolygon, 3);
  glTranslatef (0.0F, -0.1F, 0.0F);
  PolyFaceConeCut (-0.2F, -0.2F, -0.4F, nbPolygon, 3);
  glScalef (1.0F, 1.5F, 1.0F);
  reactor_anim (1.0F, true, general_animation); // Flamme
  glPopMatrix ();

  glPushMatrix ();
  material_grey (); // Échelle
  glRotatef (90.0F, 0.0F, 1.0F, 0.0F);
  glTranslatef (1.3F, 0.8F, -0.1F);
  
  glPushMatrix ();
  glRotatef (90.0F, 0.0F, 0.0F, 1.0F);
  PolyFaceCylindre (0.3F, 0.015F, 4, 3, false);
  glTranslatef (0.0F, 0.0F, 0.2F);
  PolyFaceCylindre (0.3F, 0.015F, 6, 3, false);
  glPopMatrix ();
  
  glRotatef (lem_anim (win_value, general_animation, anim_win_offset), 0.0F, 0.0F, 1.0F);
  glPushMatrix ();
  glRotatef (-90.0F, 0.0F, 0.0F, 1.0F);
  PolyFaceCylindre (1.2F, 0.015F, 4, 3, false);
  glTranslatef (0.0F, 0.0F, 0.2F);
  PolyFaceCylindre (1.2F, 0.015F, 6, 3, false);
  glPopMatrix ();
  
  for (int i = 0 ; i < 4 ; i++) {
    glPushMatrix ();
    glTranslatef (1.2F * (i / 2), 0.0F, 0.2F * (i % 2));
    PolyFaceCube (0.05F, 1, 5);
    glPopMatrix ();
  }
  
  glRotatef (90.0F, 1.0F, 0.0F, 0.0F);
  for (int i = 0 ; i <= 8 ; i++) {
    glPushMatrix ();
    glTranslatef (0.15F * i, 0.0F, 0.0F);
    PolyFaceCylindre (0.2F, 0.01F, 4, 3, false);
    glPopMatrix ();
  }
  glPopMatrix ();
  
  glPopMatrix ();
}

void rotation_update (int x, int y, int wTx, int wTy, float* rotation_direction, float* rotation_power) {
  *rotation_direction = 90.0F - 180.0F * atanf (-(y - wTy / 2) / (abs (x - wTx / 2) > 0.02 ? (x - wTx / 2) : 0.02)) / M_PI + (x >= wTx / 2 ? 180.0 : 0.0);
  *rotation_power = sqrt ((float) (x - wTx / 2) * (x - wTx / 2) + (y - wTy / 2) * (y - wTy / 2)) / ((wTx + wTy) / 2.0);
}
