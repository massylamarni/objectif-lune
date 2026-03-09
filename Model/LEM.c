 /* Modélisation d'un atterisseur spatial        */ 
 /*                                              */ 
 /* Projet Objectif Lune                         */ 

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "customPreset.h"

 /* Variables globales                           */ 

float black[] =     { 0.0F, 0.0F, 0.0F, 1.0F };
float dark_grey[] = { 0.2F, 0.2F, 0.2F, 1.0F };
float grey[] =      { 0.5F, 0.5F, 0.5F, 1.0F };
float gold[] =      { 0.9F, 0.6F, 0.1F, 1.0F };
float red[] =       { 1.0F, 0.0F, 0.0F, 1.0F };
float green[] =     { 0.0F, 1.0F, 0.0F, 1.0F };
float blue[] =      { 0.0F, 0.0F, 1.0F, 1.0F };
float rose[] =      { 1.0F, 0.9F, 0.9F, 1.0F };
float white[] =     { 1.0F, 1.0F, 1.0F, 1.0F };

float anim_LEM_offset = 0.0F;
bool win_value = false;

 /* Fonction d'initialisation des paramètres     */ 
 /* OpenGL ne changeant pas ou peu au cours de   */ 
 /* la vie du programme                          */ 

void material_gold () {
  //printf ("Material GOLD\n");
  
  glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE,  gold);
  glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, grey);
  glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT,  black);
  glMaterialfv (GL_FRONT_AND_BACK, GL_EMISSION, black);
  glMaterialf  (GL_FRONT_AND_BACK, GL_SHININESS, 120.0F);
  
  glColor4fv (gold);
}

void material_grey () {
  //printf ("Material GREY\n");
  
  glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE,  grey);
  glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, dark_grey);
  glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT,  black);
  glMaterialfv (GL_FRONT_AND_BACK, GL_EMISSION, black);
  glMaterialf  (GL_FRONT_AND_BACK, GL_SHININESS, 100.0F);
  
  glColor4fv (grey);
}

void material_dark_grey () {
  //printf ("Material DARK GREY\n");
  
  glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE,  dark_grey);
  glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, grey);
  glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT,  black);
  glMaterialfv (GL_FRONT_AND_BACK, GL_EMISSION, black);
  glMaterialf  (GL_FRONT_AND_BACK, GL_SHININESS, 70.0F);
  
  glColor4fv (dark_grey);
}

void material_red () {
  //printf ("Material RED\n");
  
  glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE,  red);
  glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, rose);
  glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT,  black);
  glMaterialfv (GL_FRONT_AND_BACK, GL_EMISSION, black);
  glMaterialf  (GL_FRONT_AND_BACK, GL_SHININESS, 100.0F);
  
  glColor4fv (red);
}

void material_white () {
  //printf ("Material WHITE\n");
  
  glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE,  white);
  glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, white);
  glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT,  black);
  glMaterialfv (GL_FRONT_AND_BACK, GL_EMISSION, black);
  glMaterialf  (GL_FRONT_AND_BACK, GL_SHININESS, 50.0F);
  
  glColor4fv (white);
}

void material_black () {
  //printf ("Material BLACK\n");
  
  glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE,  black);
  glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, white);
  glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT,  black);
  glMaterialfv (GL_FRONT_AND_BACK, GL_EMISSION, black);
  glMaterialf  (GL_FRONT_AND_BACK, GL_SHININESS, 100.0F);
  
  glColor4fv (black);
}

void test_light () {
  glPushMatrix ();
  
  float pos[] = {(0.001F * (prst_xMouse - prst_wTx / 2)), 0.2F, (0.001F * (prst_yMouse - prst_wTy / 4)), 1.0F};
  glEnable (GL_LIGHT1);
  glDisable (GL_LIGHT0);
  glLightfv (GL_LIGHT1, GL_DIFFUSE, white);
  glLightfv (GL_LIGHT1, GL_SPECULAR, white);
  glLightfv (GL_LIGHT1, GL_POSITION, pos);
  
  material_white ();
  glBegin(GL_LINES);
  glVertex3f ((0.001F * (prst_xMouse - prst_wTx / 2)), 0.2F, (0.001F * (prst_yMouse - prst_wTy / 4)));
  glVertex3f (0.0F, 0.0F, 0.0F);
  glEnd();
  
  glTranslatef ((0.001F * (prst_xMouse - prst_wTx / 2)), 0.2F, (0.001F * (prst_yMouse - prst_wTy / 4)));
  glutSolidSphere (0.05, 16, 16);
  
  glPopMatrix ();
}

void init (void) {
  glEnable (GL_LIGHTING);
  glEnable (GL_LIGHT0);
  
  glLightfv (GL_LIGHT0, GL_DIFFUSE,  white);
  glLightfv (GL_LIGHT0, GL_SPECULAR, white);
  glLightfv (GL_LIGHT0, GL_AMBIENT,  white);
  glLightfv (GL_LIGHT0, GL_AMBIENT,  white);
  
  glColorMaterial (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  
  glDepthFunc (GL_LESS);
  glEnable (GL_DEPTH_TEST);
  glEnable (GL_NORMALIZE);
  glClearColor (0.1F, 0.3F, 0.2F, 1.0F);
}

float textureRandom () {
  return (((float) rand ()) / RAND_MAX - 0.5F) * 0.05F;
}

 /* Dessin de la Scène                           */
void PolyFaceCylindre (float hauteur, float rayon, int ns, float randomTexture) {
  glPushMatrix ();
  
  float x_v, y_v, hauteur_step;
  
  for (int i = 0 ; i < ns ; i++) {
    glBegin (GL_QUAD_STRIP);
    hauteur_step = i * hauteur / ns;
    for (int j = 0 ; j <= ns ; j++) {
      x_v = rayon * sin (j * 2 * M_PI / ns);
      y_v = rayon * cos (j * 2 * M_PI / ns);
      if (randomTexture) {
        glNormal3d (x_v + textureRandom () * 0.1, textureRandom () * 0.2, y_v + textureRandom () * 0.1);
      }
      else {
        glNormal3d (x_v, 0.0, y_v);
      }
      glVertex3d (x_v, hauteur_step + hauteur / ns, y_v);
      glVertex3d (x_v, hauteur_step, y_v);
    }
    glEnd ();
  }
  
  glPopMatrix ();
}

void PolyFaceConeCut (float hauteur, float rayon_A, float rayon_B, int ns) {
  glPushMatrix ();
  
  float cos_v, sin_v, x_v, y_v, hauteur_step;
  float rayon_step = (rayon_B - rayon_A) / ns;
  
  for (int i = 0 ; i < ns ; i++) {
    glBegin (GL_QUAD_STRIP);
    hauteur_step = i * hauteur / ns;
    for (int j = 0 ; j <= ns ; j++) {
      
      sin_v = sin (j * 2 * M_PI / ns);
      cos_v = cos (j * 2 * M_PI / ns);
      
      x_v = (rayon_A + rayon_step * (i + 1)) * sin_v;
      y_v = (rayon_A + rayon_step * (i + 1)) * cos_v;
      
      glNormal3d (sin (j * 2 * M_PI / ns), -(rayon_B - rayon_A) / hauteur, cos (j * 2 * M_PI / ns));
      //glNormal3d (0.0F, rayon_B - rayon_A, -hauteur);
      glVertex3d (x_v, hauteur_step + hauteur / ns, y_v);
      x_v = (rayon_A + rayon_step * i) * sin_v;
      y_v = (rayon_A + rayon_step * i) * cos_v;
      glVertex3d (x_v, hauteur_step, y_v);
    }
    glEnd ();
  }
  
  glPopMatrix ();
}

void PolyFacePrism (int face, int total_face, float height, float length_A, float length_B, int nbPolygon, bool closed, bool randomTexture) {
  glPushMatrix ();
  
  float cos_A, sin_A, cos_B, sin_B;
  
  /* Tube */
  float length_C = (length_A - length_B) / nbPolygon;
  glBegin (GL_QUADS);
  
  for (int i = 0 ; i < face ; i++) {
    cos_A = cos (i * M_PI * 2 / total_face); // Base de face
    sin_A = sin (i * M_PI * 2 / total_face);
    cos_B = (cos ((i + 1) * M_PI * 2 / total_face) - cos_A) / nbPolygon; // Décalage latéral
    sin_B = (sin ((i + 1) * M_PI * 2 / total_face) - sin_A) / nbPolygon;
    
    
    srand (i * 123456);
    for (int c = 0 ; c < nbPolygon ; c++) {
      for (int d = 0 ; d < nbPolygon ; d++) {
        if (randomTexture) {
          glNormal3f (cos ((i + 0.5F) * M_PI * 2 / total_face) + textureRandom () * 4, textureRandom (), sin ((i + 0.5F) * M_PI * 2 / total_face) + textureRandom () * 4);
        }
        else {
          glNormal3f (cos ((i + 0.5F) * M_PI * 2 / total_face), (length_A - length_B) / height, sin ((i + 0.5F) * M_PI * 2 / total_face));
        }
        glVertex3f ((cos_A + c * cos_B) * (length_A - length_C * d),             d * height / nbPolygon, (sin_A + c * sin_B) * (length_A - length_C * d));
        glVertex3f ((cos_A + c * cos_B) * (length_A - length_C * (d + 1)),       (d + 1) * height / nbPolygon, (sin_A + c * sin_B) * (length_A - length_C * (d + 1)));
        glVertex3f ((cos_A + (c + 1) * cos_B) * (length_A - length_C * (d + 1)), (d + 1) * height / nbPolygon, (sin_A + (c + 1) * sin_B) * (length_A - length_C * (d + 1)));
        glVertex3f ((cos_A + (c + 1) * cos_B) * (length_A - length_C * d),       d * height / nbPolygon, (sin_A + (c + 1) * sin_B) * (length_A - length_C * d));
      }
    }
  }
  
  glEnd ();
  
  if (closed) { 
    /* Face A */
    glBegin (GL_TRIANGLE_FAN);
    glNormal3f (textureRandom () * 2, -1.0F - textureRandom () / 2, textureRandom () * 2);
    glVertex3f (0.0F, 0.0F, 0.0F);
    for (int i = 0 ; i <= face ; i++) {
      cos_A = cos (i * M_PI * 2 / total_face) * length_A / nbPolygon;
      sin_A = sin (i * M_PI * 2 / total_face) * length_A / nbPolygon;
      
      glNormal3f (textureRandom () * 2, -1.0F - textureRandom () / 2, textureRandom () * 2);
      glVertex3f (cos_A, 0.0F, sin_A);
    }
    glEnd ();
    
    for (int e = 1 ; e < nbPolygon ; e++) {
      glBegin (GL_QUAD_STRIP);
      for (int i = 0 ; i <= face ; i++) {
        cos_A = -cos (i * M_PI * 2 / total_face) * length_A * (e + 1) / nbPolygon;
        sin_A = sin (i * M_PI * 2 / total_face) * length_A * (e + 1) / nbPolygon;
        
        glNormal3f (textureRandom () * 2, -1.0F - textureRandom () / 2, textureRandom () * 2);
        glVertex3f (cos_A, 0.0F, sin_A);

        cos_A = -cos (i * M_PI * 2 / total_face) * length_A * e / nbPolygon;
        sin_A = sin (i * M_PI * 2 / total_face) * length_A * e / nbPolygon;
        
        glNormal3f (textureRandom () * 2, -1.0F - textureRandom () / 2, textureRandom () * 2);
        glVertex3f (cos_A, 0.0F, sin_A);

      }
      glEnd ();
    }
    
    /* Face B */
    glBegin (GL_TRIANGLE_FAN);
    glNormal3f (textureRandom () * 2, 1.0F + textureRandom () / 2, textureRandom () * 2);
    glVertex3f (0.0F, height, 0.0F);
    for (int i = 0 ; i <= face ; i++) {
      cos_A = -cos (i * M_PI * 2 / total_face) * length_B / nbPolygon;
      sin_A = sin (i * M_PI * 2 / total_face) * length_B / nbPolygon;
      
      glNormal3f (textureRandom () * 2, 1.0F + textureRandom () / 2, textureRandom () * 2);
      glVertex3f (cos_A, height, sin_A);
    }
    glEnd ();
    
    for (int e = 1 ; e < nbPolygon ; e++) {
      glBegin (GL_QUAD_STRIP);
      for (int i = 0 ; i <= face ; i++) {
        cos_A = cos (i * M_PI * 2 / total_face) * length_B * (e + 1) / nbPolygon;
        sin_A = sin (i * M_PI * 2 / total_face) * length_B * (e + 1) / nbPolygon;
        
        glNormal3f (textureRandom () * 2, 1.0F + textureRandom () / 2, textureRandom () * 2);
        glVertex3f (cos_A, height, sin_A);

        cos_A = cos (i * M_PI * 2 / total_face) * length_B * e / nbPolygon;
        sin_A = sin (i * M_PI * 2 / total_face) * length_B * e / nbPolygon;
        
        glNormal3f (textureRandom () * 2, 1.0F + textureRandom () / 2, textureRandom () * 2);
        glVertex3f (cos_A, height, sin_A);

      }
      glEnd ();
    }
  }
  glPopMatrix ();
}

void PolyFaceSurface (float size_x, float size_y, int nbPolygon_x, int nbPolygon_y, bool randomTexture) {
  glPushMatrix ();
  
  float step_x = size_x / nbPolygon_x;
  float step_y = size_y / nbPolygon_y;
  if (randomTexture) {
    for (int x = 0 ; x < nbPolygon_x ; x++) {
      glBegin (GL_QUAD_STRIP);
      for (int y = 0 ; y <= nbPolygon_y ; y++) {
        glNormal3f (textureRandom () * 2, textureRandom () * 2, 1.0F - textureRandom () / 2);
        glVertex3f (-size_x / 2 + x * step_x,       -size_y / 2 + y * step_y, 0.0F);
        
        glNormal3f (textureRandom () * 2, textureRandom () * 2, 1.0F - textureRandom () / 2);
        glVertex3f (-size_x / 2 + (x + 1) * step_x, -size_y / 2 + y * step_y, 0.0F);
      }
      glEnd ();
    }
  }
  else {
    glNormal3f (0.0F, 0.0F, 1.0F);
    for (int x = 0 ; x < nbPolygon_x ; x++) {
      glBegin (GL_QUAD_STRIP);
      for (int y = 0 ; y <= nbPolygon_y ; y++) {
        glVertex3f (-size_x / 2 + x * step_x,       -size_y / 2 + y * step_y, 0.0F);
        glVertex3f (-size_x / 2 + (x + 1) * step_x, -size_y / 2 + y * step_y, 0.0F);
      }
      glEnd ();
    }
  }
  
  glPopMatrix ();
}

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

float LEM_anim () {
  if (win_value) {
    if (prst_animation - anim_LEM_offset > 100) {
      return -60.0F;
    }
    return (prst_animation - anim_LEM_offset) * -1.8F + 120.0F;
  }
  else {
    return 120.0F;
  }
}

void LEM (void) {
  glPushMatrix ();
  
  material_gold ();
  PolyFacePrism (8, 8, 1.0F, 1.0823922F, 1.0823922F, prst_nbPolygon, true, true); // Corps
  // 1.0823922F == 1 / cos (22.5 * 2 * M_PI / 360) ou le rayon du cercle inscrit d'un octogone de cercle circonscris de 1
  
  glRotatef (22.5F, 0.0F, 1.0F, 0.0F);
  for (int i = 0 ; i < 4 ; i++) { // Pieds
    glPushMatrix ();
    glRotatef (i * 90.0F, 0.0F, 1.0F, 0.0F);
    glTranslatef (1.3F, 0.15F, 0.0F);
    PolyFaceCylindre (0.5F, 0.05F, prst_nbPolygon, true);
    
    glPushMatrix ();
    glRotatef (105.0F, 0.0F, 0.0F, 1.0F);
    PolyFaceCylindre (0.35F, 0.05F, prst_nbPolygon, true);
    glPopMatrix ();
    
    {
      glPushMatrix ();
      glTranslatef (0.0F, 0.5F, 0.0F);
      
      glPushMatrix ();
      
      glutSolidSphere (0.05, prst_nbPolygon / 2, prst_nbPolygon / 2);
      
      glRotatef (50.0F, 0.0F, 0.0F, 1.0F);
      PolyFaceCylindre (0.45F, 0.05F, prst_nbPolygon, true);
      glPopMatrix ();
      
      glRotatef (-150.0F, 0.0F, 0.0F, 1.0F);
      PolyFaceCylindre (1.0F, 0.05F, prst_nbPolygon, true);
      
      glPopMatrix ();
    }
    
    glRotatef (-125.0F, 0.0F, 0.0F, 1.0F);
    PolyFaceCylindre (0.6F, 0.05F, prst_nbPolygon, true);
    
    glTranslatef (0.0F, 0.6F, 0.0F);
    glRotatef (-35.0F, 0.0F, 0.0F, 1.0F);
    PolyFaceCylindre (0.2F, 0.05F, prst_nbPolygon, true);
    
    glTranslatef (0.0F, 0.175F, 0.0F);
    glRotatef (-20.0F, 0.0F, 0.0F, 1.0F);
    PolyFacePrism (8, 8, 0.05F, 0.2F, 0.17F, prst_nbPolygon / 2, true, true);
    
    glPopMatrix ();
  }
  
  material_grey ();
  
  glPushMatrix (); // Tête
  
  glTranslatef (0.0F, 1.0F, 1.0F);
  
  glRotatef (-90.0F, 1.0F, 0.0F, 0.0F);
  PolyFacePrism (8, 16, 0.5F, 0.2F, 0.6F, prst_nbPolygon / 2, true, false);
  glTranslatef (0.0F, 0.5F, 0.0F);
  PolyFacePrism (8, 16, 0.25F, 0.6F, 1.0F, prst_nbPolygon / 2, false, false);
  glTranslatef (0.0F, 0.25F, 0.0F);
  PolyFacePrism (8, 16, 0.5F, 1.0F, 1.0F, prst_nbPolygon / 2, false, false);
  glTranslatef (0.0F, 0.5F, 0.0F);//*/
  PolyFacePrism (8, 16, 0.25F, 1.0F, 0.6F, prst_nbPolygon / 2, true, false);
  glTranslatef (0.0F, 0.25F, 0.0F);
  
  glPushMatrix ();
  glTranslatef (0.0F, 0.125F, 0.3F);
  PolyFaceSurface (0.8F, 0.25F, prst_nbPolygon, prst_nbPolygon / 2, false);
  glPopMatrix ();
  glPushMatrix ();
  glTranslatef (0.0F, 0.375F, 0.3F);
  PolyFaceSurface (0.4F, 0.25F, prst_nbPolygon / 2, prst_nbPolygon / 2, false);
  glPopMatrix ();
  glPushMatrix ();
  glTranslatef (0.0F, 0.5F, 0.15F);
  glRotatef (-90.0F, 1.0F, 0.0F, 0.0F);
  PolyFaceSurface (0.4F, 0.3F, prst_nbPolygon / 2, prst_nbPolygon / 2, false);
  glPopMatrix ();
  glPushMatrix ();
  glTranslatef (0.0F, 0.25F, 0.15F);
  glRotatef (-90.0F, 1.0F, 0.0F, 0.0F);
  PolyFaceSurface (0.8F, 0.3F, prst_nbPolygon, prst_nbPolygon / 2, false);
  glPopMatrix ();
  glPushMatrix ();
  glTranslatef (0.4F, 0.125F, 0.15F);
  glRotatef (90.0F, 0.0F, 1.0F, 0.0F);
  PolyFaceSurface (0.3F, 0.25F, prst_nbPolygon / 2, prst_nbPolygon / 2, false);
  glPopMatrix ();
  glPushMatrix ();
  glTranslatef (-0.4F, 0.125F, 0.15F);
  glRotatef (-90.0F, 0.0F, 1.0F, 0.0F);
  PolyFaceSurface (0.3F, 0.25F, prst_nbPolygon / 2, prst_nbPolygon / 2, false);
  glPopMatrix ();
  glPushMatrix ();
  glTranslatef (0.2F, 0.375F, 0.15F);
  glRotatef (90.0F, 0.0F, 1.0F, 0.0F);
  PolyFaceSurface (0.3F, 0.25F, prst_nbPolygon / 2, prst_nbPolygon / 2, false);
  glPopMatrix ();
  glPushMatrix ();
  glTranslatef (-0.2F, 0.375F, 0.15F);
  glRotatef (-90.0F, 0.0F, 1.0F, 0.0F);
  PolyFaceSurface (0.3F, 0.25F, prst_nbPolygon / 2, prst_nbPolygon / 2, false);
  glPopMatrix ();
  
  glPushMatrix ();
  glTranslatef (0.0F, 0.125F, 0.3F + tan (30.0 * 2 * M_PI / 360) / 8);
  glRotatef (-30.0F, 1.0F, 0.0F, 0.0F);
  PolyFaceSurface (0.4F, 1.0F / (cos (30.0 * 2 * M_PI / 360) * 4.0F), prst_nbPolygon / 2, prst_nbPolygon / 2, false);
  glPushMatrix ();
  glTranslatef (0.2F, 0.0F, -0.15F);
  glRotatef (90.0F, 0.0F, 1.0F, 0.0F);
  PolyFaceSurface (0.3F, 1.0F / (cos (30.0 * 2 * M_PI / 360) * 4.0F), prst_nbPolygon / 2, prst_nbPolygon / 2, false);
  glPopMatrix ();
  glPushMatrix ();
  glTranslatef (-0.2F, 0.0F, -0.15F);
  glRotatef (-90.0F, 0.0F, 1.0F, 0.0F);
  PolyFaceSurface (0.3F, 1.0F / (cos (30.0 * 2 * M_PI / 360) * 4.0F), prst_nbPolygon / 2, prst_nbPolygon / 2, false);
  glPopMatrix ();
  glPopMatrix ();
  
  glPopMatrix ();
  
  glPushMatrix ();
  material_dark_grey (); // Tuyère
  glRotatef (180.0F, 1.0F, 0.0F, 0.0F);
  PolyFaceConeCut (0.3F, 0.3F, 0.4F, prst_nbPolygon);
  glRotatef (180.0F, 1.0F, 0.0F, 0.0F);
  PolyFaceConeCut (-0.1F, 0.0F, -0.2F, prst_nbPolygon);
  glTranslatef (0.0F, -0.1F, 0.0F);
  PolyFaceConeCut (-0.2F, -0.2F, -0.4F, prst_nbPolygon);
  glPopMatrix ();

  glPushMatrix ();
  material_grey (); // Échelle
  glRotatef (90.0F, 0.0F, 1.0F, 0.0F);
  glTranslatef (1.3F, 0.8F, -0.1F);
  
  glPushMatrix ();
  glRotatef (90.0F, 0.0F, 0.0F, 1.0F);
  PolyFaceCylindre (0.3F, 0.015F, 4, false);
  glTranslatef (0.0F, 0.0F, 0.2F);
  PolyFaceCylindre (0.3F, 0.015F, 6, false);
  glPopMatrix ();
  
  glRotatef (LEM_anim (), 0.0F, 0.0F, 1.0F);
  glPushMatrix ();
  glRotatef (-90.0F, 0.0F, 0.0F, 1.0F);
  PolyFaceCylindre (1.2F, 0.015F, 4, false);
  glTranslatef (0.0F, 0.0F, 0.2F);
  PolyFaceCylindre (1.2F, 0.015F, 6, false);
  glPopMatrix ();
  
  for (int i = 0 ; i < 4 ; i++) {
    glPushMatrix ();
    glTranslatef (1.2F * (i / 2), 0.0F, 0.2F * (i % 2));
    glutSolidCube (0.05);
    glPopMatrix ();
  }
  
  glRotatef (90.0F, 1.0F, 0.0F, 0.0F);
  for (int i = 0 ; i <= 8 ; i++) {
    glPushMatrix ();
    glTranslatef (0.15F * i, 0.0F, 0.0F);
    PolyFaceCylindre (0.2F, 0.01F, 4, false);
    glPopMatrix ();
  }
  glPopMatrix ();
  
  glPopMatrix ();
}

void scene (void) {
  glPushMatrix ();
  
  glTranslatef (0.0F,-1.0F, 0.0F);
  
  LEM ();
  
  glPopMatrix ();
}

 /* Fonction executee lors d'un rafraichissement */ 
 /* de la fenetre de dessin                      */ 

void display (void) {
 /* Préparation                                  */
  printf ("D\n");
  
  if (prst_bufferBitMode == 0) {
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }
  else if (prst_bufferBitMode == 1) {
    glClear (GL_DEPTH_BUFFER_BIT);
  }
  else if (prst_bufferBitMode == 2) {
    glClear (GL_COLOR_BUFFER_BIT);
  }
  
 /* Modélisation Géométrique                     */
  glPushMatrix ();
  
  glTranslatef(0.0F, 0.0F, -5.0F);
  //test_light ();
  glRotatef (prst_alpha, 1.0F, 0.0F, 0.0F);
  glRotatef (prst_beta, 0.0F, 1.0F, 0.0F);
  glScalef (prst_size, prst_size, prst_size);
  
  scene ();
  
  glPopMatrix ();
  
 /* Rastérisation                                */
  glFlush ();
  glutSwapBuffers ();
 /* Erreurs                                      */
  
  int error = glGetError ();
  if ( error != GL_NO_ERROR )
    printf ("Attention erreur %d\n", error);
}

 /* Fonction executee lors d'un changement       */ 
 /* de la taille de la fenetre OpenGL            */ 

void reshape (int wx, int wy) {
  printf ("R\n");
  prst_wTx = wx; 
  prst_wTy = wy; 
  glViewport (0, 0, wx, wy); 
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  //glOrtho (-4.0, 4.0, -4.0, 4.0, -10.0, 10.0);
  glFrustum (-1.0, 1.0, -1.0 * wy / wx, 1.0 * wy / wx, prst_fov , 20.0 + prst_fov);
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity ();
}

 /* Fonction exécutée lorsqu'aucun évènement     */ 
 /* n'est en file d'attente                      */ 

void idle (void) {
  printf ("I\n");
  prst_animation += ((float) prst_animationSpeed) / 5.0F;
  if (prst_rotation && prst_rotationSpeed != 0) {
    prst_beta += (float) prst_rotationSpeed / 10;
    //sleep (1); // Anti-Lag
    glutPostRedisplay ();
  }
}

 /* Fonction exécutée lors de l'appui            */ 
 /* d'une touche alphanumérique du clavier       */ 

void keyboard (unsigned char key, int x, int y) {
  printf ("K  %d %4c %4d %4d\n", key, key, x, y);
  
  if (stdKeyboard (key, x, y)) {
    reshape (prst_wTx, prst_wTy);
  }
  
  keyboardAssistIntLoop (&prst_sceneId, key, 'M', 'm', 0, 3);
  
  printf("Bool %d\n", keyboardAssistFloatProportional (&prst_rotationSpeed, key, (char) GLUT_KEY_INSERT, 0x7f, -3600.0F, 3600.0F, 0.05F, 0.05F));
  if (key == 'w') { // Active Win condition
    win_value = !win_value;
    if (win_value) {
      anim_LEM_offset = prst_animation;
    }
  }
  else if (keyboardAssistBool (&prst_animated, key, 0X0D)) { // Entrée - Pause Animation
    printf ("Animation\n");    
    if (prst_animated) {
      glutIdleFunc (NULL);
    }
    else {
      glutIdleFunc (idle);
    }
  }
  else if (key == 0x7f) { // Vitesse de la Rotation
    //prst_rotationSpeed--;
    printf ("New Rotation Speed : %f\n", prst_rotationSpeed);
  }
  else if (key == 0X1B) { // Échap - Sortie
    exit (0);
  }
  glutPostRedisplay ();
}

 /* Fonction executee lors de l'appui            */ 
 /* d'une touche speciale du clavier :           */ 
 /*   - touches de curseur                       */ 
 /*   - touches de fonction                      */ 

void special (int specialKey, int x, int y) {
  printf ("S  %4d %4d %4d\n", specialKey, x, y);
  
  keyboardAssistFloatProportional (&prst_manualSpeed, (char) specialKey, (char) GLUT_KEY_HOME, (char) GLUT_KEY_END, 0.0F, 3600.0F, 0.0F, 0.05F);
  keyboardAssistFloatProportional (&prst_rotationSpeed, (char) specialKey, (char) GLUT_KEY_INSERT, (char) 0x7f, 3600.0F, 3600.0F, 0.05F, 0.05F);
  
  if (specialKey == GLUT_KEY_PAGE_UP) { // Vitesse de l'animation de base
    prst_animationSpeed++;
    printf ("New Animation Speed : %d\n", prst_animationSpeed);
  }
  else if (specialKey == GLUT_KEY_PAGE_DOWN) {
    prst_animationSpeed--;
    printf ("New Animation Speed : %d\n", prst_animationSpeed);
  }
  else if (specialKey == GLUT_KEY_INSERT) { // Vitesse de la Rotation
    //prst_rotationSpeed++;
    printf ("New Rotation Speed : %f\n", prst_rotationSpeed);
  }
  else if (specialKey == GLUT_KEY_RIGHT) { // Mouvement de la caméra manuelle
    prst_beta += prst_manualSpeed;
  }
  else if (specialKey == GLUT_KEY_LEFT) {
    prst_beta -= prst_manualSpeed;
  }
  else if (specialKey == GLUT_KEY_UP) {
    prst_alpha += prst_manualSpeed;
  }
  else if (specialKey == GLUT_KEY_DOWN) {
    prst_alpha -= prst_manualSpeed;
  }
  else if (specialKey == GLUT_KEY_HOME) { // Vitesse de la caméra manuelle
    //prst_manualSpeed += 0.5;
    printf ("New Camera Speed : %f\n", prst_manualSpeed);
  }
  else if (specialKey == GLUT_KEY_END) {
    //prst_manualSpeed -= 0.5;
    printf ("New Camera Speed : %f\n", prst_manualSpeed);
  }
  glutPostRedisplay ();
}

 /* Fonction executee lors de l'utilisation      */ 
 /* de la souris sur la fenetre                  */ 

void mouse (int button, int state, int x, int y) {
  printf ("M  %4d %4d %4d %4d\n", button, state, x, y);
  prst_xMouse = x;
  prst_yMouse = y;
  if (button == 0) {
    prst_xMouse = x;
    prst_yMouse = y;
    prst_rotation = (state == 1);
  }
  else if (button == 2 && state == 0) {
    prst_rotationSpeed = - prst_rotationSpeed;
  }
}

 /* Fonction executee lors du passage            */ 
 /* de la souris sur la fenetre                  */ 
 /* avec un bouton presse                        */ 

void mouseMotion (int x, int y) {
  printf ("MM %4d %4d\n", x, y);
  prst_beta += x - prst_xMouse;
  prst_alpha += y - prst_yMouse;
  prst_xMouse = x;
  prst_yMouse = y;
  glutPostRedisplay ();
}

 /* Fonction executee lors du passage            */ 
 /* de la souris sur la fenetre                  */ 
 /* sans bouton presse                           */ 

/*void passiveMouseMotion (int x, int y) {
  printf ("PM %4d %4d\n", x, y);
  glutPostRedisplay ();
}*/

 /* Fonction exécutée automatiquement            */ 
 /* lors de l'exécution de la fonction exit ()   */ 

void clean (void) {
  printf ("Bye\n");
}

 /* Fonction principale                          */ 

int main (int argc, char **argv) {

  atexit (clean);

  glutInit (&argc, argv);
  glutInitDisplayMode (GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
  glutInitWindowSize (prst_wTx, prst_wTy);
  glutInitWindowPosition (prst_wPx, prst_wPy);
  glutCreateWindow ("Gestion evenementielle de GLUt");
  init ();
  
  material_red ();
  
  glutKeyboardFunc (keyboard);
  glutSpecialFunc (special);
  glutMouseFunc (mouse);
  glutMotionFunc (mouseMotion);
  //glutPassiveMotionFunc (passiveMouseMotion);
  glutReshapeFunc (reshape);
  glutIdleFunc (idle);
  //glutIdleFunc (NULL);
  glutDisplayFunc (display);
  glutMainLoop ();
  return (0); // Won't be reach cause the normal way to stop is exit the MainLoop
}
