#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

float textureRandom () {
  return (((float) rand ()) / RAND_MAX - 0.5F) * 0.05F;
}

void texCoord (int index, float u, float v) {
  if (index == 0) { // No Change
    glTexCoord2f (u, v);
  }
  else if (index == 1) { // First Third
    glTexCoord2f (u / 3.0F, v);
  }
  else if (index == 2) { // Second Third
    glTexCoord2f ((u + 1.0F) / 3.0F, v);
  }
  else if (index == 3) { // Third Third
    glTexCoord2f ((v + 2.0F) / 3.0F, u);
  }
  else if (index == 4) { // Half First Third
    glTexCoord2f (u / 6.0F, v);
  }
  else if (index == 5) { // Mini Second Third
    glTexCoord2f ((u + 2.5F) / 6.0F, (v + 0.5F) / 2.0);
  }
}

void PolyFaceCylindre (float hauteur, float rayon, int ns, int tex_part_index, bool randomTexture) {
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
      texCoord (tex_part_index, (float) j / ns, (float) (i + 1) / ns);
      glVertex3d (x_v, hauteur_step + hauteur / ns, y_v);
      
      texCoord (tex_part_index, (float) j / ns, (float) i / ns);
      glVertex3d (x_v, hauteur_step, y_v);
    }
    glEnd ();
  }
  
  glPopMatrix ();
}

void PolyFaceConeCut (float hauteur, float rayon_A, float rayon_B, int ns, int tex_part_index) {
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
      texCoord (tex_part_index, (float) (i + 1) / ns, (float) j / ns);
      glVertex3d (x_v, hauteur_step + hauteur / ns, y_v);
      x_v = (rayon_A + rayon_step * i) * sin_v;
      y_v = (rayon_A + rayon_step * i) * cos_v;
      texCoord (tex_part_index, (float) i / ns, (float) j / ns);
      glVertex3d (x_v, hauteur_step, y_v);
    }
    glEnd ();
  }
  
  glPopMatrix ();
}

void PolyFacePrism (int face, int total_face, float height, float length_A, float length_B, int nbPolygon, bool closed, int tex_part_index, bool randomTexture) {
  glPushMatrix ();
  
  float cos_A, sin_A, cos_B, sin_B;
  
  /* Tube */
  float length_C = (length_A - length_B) / nbPolygon;
  
  for (int i = 0 ; i < face ; i++) {
    cos_A = cos (i * M_PI * 2 / total_face); // Base de face
    sin_A = sin (i * M_PI * 2 / total_face);
    cos_B = (cos ((i + 1) * M_PI * 2 / total_face) - cos_A) / nbPolygon; // Décalage latéral
    sin_B = (sin ((i + 1) * M_PI * 2 / total_face) - sin_A) / nbPolygon;
    
    
    srand (i * 123456);
    for (int c = 0 ; c < nbPolygon ; c++) {
      glBegin (GL_QUAD_STRIP);
      for (int d = 0 ; d <= nbPolygon ; d++) {
        if (randomTexture) {
          glNormal3f (cos ((i + 0.5F) * M_PI * 2 / total_face) + textureRandom () * 4, textureRandom (), sin ((i + 0.5F) * M_PI * 2 / total_face) + textureRandom () * 4);
        }
        else {
          glNormal3f (cos ((i + 0.5F) * M_PI * 2 / total_face), (length_A - length_B) / height, sin ((i + 0.5F) * M_PI * 2 / total_face));
        }
        texCoord (tex_part_index, (float) c / nbPolygon, (float) d / nbPolygon);
        glVertex3f ((cos_A + c * cos_B) * (length_A - length_C * d),             d * height / nbPolygon, (sin_A + c * sin_B) * (length_A - length_C * d));
        texCoord (tex_part_index, (float) (c + 1) / nbPolygon, (float) d / nbPolygon);
        glVertex3f ((cos_A + (c + 1) * cos_B) * (length_A - length_C * d),       d * height / nbPolygon, (sin_A + (c + 1) * sin_B) * (length_A - length_C * d));
      }
      glEnd ();
    }
  }
  
  
  if (closed) {
    for (int e = 0 ; e < nbPolygon ; e++) {
      glBegin (GL_QUAD_STRIP);
      for (int i = 0 ; i <= face ; i++) {
        cos_A = -cos (i * M_PI * 2 / total_face) * length_A * (e + 1) / nbPolygon;
        sin_A = sin (i * M_PI * 2 / total_face) * length_A * (e + 1) / nbPolygon;
        
        glNormal3f (textureRandom () * 2, -1.0F - textureRandom () / 2, textureRandom () * 2);
        texCoord (tex_part_index, (float) i / face, (float) (e + 1) / nbPolygon / 2.0F + 0.5f);
        glVertex3f (cos_A, 0.0F, sin_A);

        cos_A = -cos (i * M_PI * 2 / total_face) * length_A * e / nbPolygon;
        sin_A = sin (i * M_PI * 2 / total_face) * length_A * e / nbPolygon;
        
        glNormal3f (textureRandom () * 2, -1.0F - textureRandom () / 2, textureRandom () * 2);
        texCoord (tex_part_index, (float) i / face, (float) e / nbPolygon / 2.0F + 0.5f);
        glVertex3f (cos_A, 0.0F, sin_A);

      }
      glEnd ();
    }
    
    /* Face B */
    for (int e = 0 ; e < nbPolygon ; e++) {
      glBegin (GL_QUAD_STRIP);
      for (int i = 0 ; i <= face ; i++) {
        cos_A = cos (i * M_PI * 2 / total_face) * length_B * (e + 1) / nbPolygon;
        sin_A = sin (i * M_PI * 2 / total_face) * length_B * (e + 1) / nbPolygon;
        
        glNormal3f (textureRandom () * 2, 1.0F + textureRandom () / 2, textureRandom () * 2);
        texCoord (tex_part_index, (float) i / face, (float) (e + 1) / nbPolygon / 2.0F + 0.5f);
        glVertex3f (cos_A, height, sin_A);

        cos_A = cos (i * M_PI * 2 / total_face) * length_B * e / nbPolygon;
        sin_A = sin (i * M_PI * 2 / total_face) * length_B * e / nbPolygon;
        
        glNormal3f (textureRandom () * 2, 1.0F + textureRandom () / 2, textureRandom () * 2);
        texCoord (tex_part_index, (float) i / face, (float) e / nbPolygon / 2.0F + 0.5f);
        glVertex3f (cos_A, height, sin_A);

      }
      glEnd ();
    }
  }
  glPopMatrix ();
}

void PolyFaceSurface (float size_x, float size_y, int nbPolygon_x, int nbPolygon_y, int tex_part_index, bool randomTexture) {
  glPushMatrix ();
  
  float step_x = size_x / nbPolygon_x;
  float step_y = size_y / nbPolygon_y;
  if (randomTexture) {
    for (int x = 0 ; x < nbPolygon_x ; x++) {
      glBegin (GL_QUAD_STRIP);
      for (int y = 0 ; y <= nbPolygon_y ; y++) {
        glNormal3f (textureRandom () * 2, textureRandom () * 2, 1.0F - textureRandom () / 2);
        texCoord (tex_part_index, (float) x / nbPolygon_x, (float) y / nbPolygon_y);
        glVertex3f (-size_x / 2 + x * step_x,       -size_y / 2 + y * step_y, 0.0F);
        
        glNormal3f (textureRandom () * 2, textureRandom () * 2, 1.0F - textureRandom () / 2);
        texCoord (tex_part_index, (float) (x + 1) / nbPolygon_x, (float) y / nbPolygon_y);
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
        texCoord (tex_part_index, (float) x / nbPolygon_x, (float) y / nbPolygon_y);
        glVertex3f (-size_x / 2 + x * step_x,       -size_y / 2 + y * step_y, 0.0F);
        texCoord (tex_part_index, (float) (x + 1) / nbPolygon_x, (float) y / nbPolygon_y);
        glVertex3f (-size_x / 2 + (x + 1) * step_x, -size_y / 2 + y * step_y, 0.0F);
      }
      glEnd ();
    }
  }
  
  glPopMatrix ();
}

void PolyFaceCube (float size, int nbPolygon, int tex_part_index) {
  glPushMatrix ();
  
  glPushMatrix ();
  glTranslatef (0.0F, 0.0F, size / 2.0F);
  PolyFaceSurface (size, size, nbPolygon, nbPolygon, tex_part_index, false);
  glPopMatrix ();
  glPushMatrix ();
  glRotatef (180.0F, 0.0F, 1.0F, 0.0F);
  glTranslatef (0.0F, 0.0F, size / 2.0F);
  PolyFaceSurface (size, size, nbPolygon, nbPolygon, tex_part_index, false);
  glPopMatrix ();
  glPushMatrix ();
  glRotatef (90.0F, 1.0F, 0.0F, 0.0F);
  glTranslatef (0.0F, 0.0F, size / 2.0F);
  PolyFaceSurface (size, size, nbPolygon, nbPolygon, tex_part_index, false);
  glPopMatrix ();
  glPushMatrix ();
  glRotatef (90.0F,-1.0F, 0.0F, 0.0F);
  glTranslatef (0.0F, 0.0F, size / 2.0F);
  PolyFaceSurface (size, size, nbPolygon, nbPolygon, tex_part_index, false);
  glPopMatrix ();
  glPushMatrix ();
  glRotatef (90.0F, 0.0F, 1.0F, 0.0F);
  glTranslatef (0.0F, 0.0F, size / 2.0F);
  PolyFaceSurface (size, size, nbPolygon, nbPolygon, tex_part_index, false);
  glPopMatrix ();
  glPushMatrix ();
  glRotatef (90.0F, 0.0F,-1.0F, 0.0F);
  glTranslatef (0.0F, 0.0F, size / 2.0F);
  PolyFaceSurface (size, size, nbPolygon, nbPolygon, tex_part_index, false);
  glPopMatrix ();
  
  glPopMatrix ();
}
