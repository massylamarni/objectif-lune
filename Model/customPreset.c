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

//#include "customPreset.h"

int prst_wTx = 800;              // Résolution horizontale de la fenêtre
int prst_wTy = 800;              // Résolution verticale de la fenêtre
int prst_wPx = 150;              // Position horizontale de la fenêtre
int prst_wPy = 75;               // Position verticale de la fenêtre
float prst_alpha = 0.0F;
float prst_beta = 0.0F;
float prst_animation = 0.0F;

int prst_bufferBitMode = 0;      // Mode Buffer GL
int prst_polygonMode = 0;        // Mode d'affichage des polygones (faces pleines / arêtes / points)
int prst_polygonModeList[] = { GL_FILL, GL_LINE, GL_POINT };
bool prst_animated = true;       // Animation
int prst_animationSpeed = 16;    // Vitesse Animation
float prst_rotationSpeed = 0.0F;      // Vitesse Rotation
float prst_manualSpeed = 3.0F;   // Vitesse Camera Manuelle
int prst_xMouse = 0;             // Abscisse de la souris
int prst_yMouse = 0;             // Ordonnée de la souris
bool prst_rotation = true;       // Rotation automatique
float prst_fov = 1.5F;           // Champs de vue

float prst_size = 1.0F;
int prst_nbPolygon = 16;
int prst_sceneId = 0;

bool prst_verbose = false;

bool keyboardAssistBool (bool* var, char current, char activation) {
  if (current == activation) {
    *var = !(*var);
    return true;
  }
  return false;
}

bool keyboardAssistInt (int* var, char current, char increment, char decrement, int min_value, int max_value) {
  if (current == increment && *var < max_value) {
    (*var)++;
    return true;
  }
  if (current == decrement && *var > min_value) {
    (*var)--;
    return true;
  }
  return false;
}

bool keyboardAssistIntLoop (int* var, char current, char increment, char decrement, int min_value, int max_value) {
  if (current == increment) {
    if (*var < max_value) {
      (*var)++;
    }
    else {
      *var = min_value;
    }
    return true;
  }
  if (current == decrement) {
    if (*var > min_value) {
      (*var)--;
    }
    else {
      *var = max_value;
    }
    return true;
  }
  return false;
}

bool keyboardAssistFloatLinear (float* var, char current, char increment, char decrement, float min_value, float max_value, float step) {
  if (current == increment && *var < max_value) {
    *var += step;
    return true;
  }
  if (current == decrement && *var > min_value) {
    *var -= step;
    return true;
  }
  return false;
}

bool keyboardAssistFloatLinearLoop (float* var, char current, char increment, char decrement, float min_value, float max_value, float step) {
  if (current == increment) {
    if (*var < max_value) {
      *var += step;
    }
    else {
      *var = min_value;
    }
    return true;
  }
  if (current == decrement) {
    if (*var > min_value) {
      *var -= step;
    }
    else {
      *var = max_value;
    }
    return true;
  }
  return false;
}

bool keyboardAssistFloatProportional (float* var, char current, char increment, char decrement, float min_value, float max_value, float step, float step_factor) {
  if (current == increment && *var < max_value) {
    *var += fabsf (*var) * step_factor + step;
    return true;
  }
  if (current == decrement && *var > min_value) {
    *var -= fabsf (*var) * step_factor + step;
    return true;
  }
  return false;
}

bool keyboardAssistFloatProportionalLoop (float* var, char current, char increment, char decrement, float min_value, float max_value, float step, float step_factor) {
  if (current == increment) {
    if (*var < max_value) {
      *var += *var * step_factor + step;
    }
    else {
      *var = min_value;
    }
    return true;
  }
  if (current == decrement) {
    if (*var > min_value) {
      *var -= *var / step_factor + step;
    }
    else {
      *var = max_value;
    }
    return true;
  }
  return false;
}

void keyboardAssistToggle (int var, char current, char activation) {
  if (current == activation) {
    if (glIsEnabled (var)) {
      glDisable(var);
    }
    else {
      glEnable(var);
    }
  }
}

bool stdKeyboard (unsigned char key, int x, int y) {
  printf ("K  %d %4c %4d %4d\n", key, key, x, y);
  bool res = false;
  
  keyboardAssistToggle (GL_DEPTH_TEST, key, 'h');
  
  keyboardAssistToggle (GL_CULL_FACE, key, 'H');
  
  keyboardAssistToggle (GL_LIGHTING, key, 'l');
  
  keyboardAssistToggle (GL_COLOR_MATERIAL, key, 'L');
  
  keyboardAssistIntLoop (&prst_bufferBitMode, key, 'P', '\0', 0, 3);
  
  if (keyboardAssistIntLoop (&prst_polygonMode, key, 'p', '\0', 0, 2)) {
    glPolygonMode (GL_FRONT_AND_BACK, prst_polygonModeList [prst_polygonMode]);
  }
  
  if (keyboardAssistFloatLinear (&prst_fov, key, 'B', 'b', 0.0F, 4.4F, 0.1F)) {
    res = true;
  }
  
  keyboardAssistInt (&prst_nbPolygon, key, 'M', 'm', 3, 1024);
  
  keyboardAssistIntLoop (&prst_sceneId, key, 'M', 'm', 0, 3);
  
  keyboardAssistFloatLinear (&prst_size, key, 'N', 'n', 0.01F, 10.0F, 0.01F);
  
  
  keyboardAssistBool (&prst_verbose, key, 'v');
  if (prst_verbose) {
    printf ("Status : ");
    if (glIsEnabled (GL_DEPTH_TEST)) {
      printf ("GL_DEPTH_TEST | ");
    }
    if (glIsEnabled (GL_CULL_FACE)) {
      printf ("GL_CULL_FACE | ");
    }
    if (glIsEnabled (GL_LIGHTING)) {
      printf ("GL_LIGHTING | ");
    }
    printf ("prst_bufferBitMode : %d | ", prst_bufferBitMode);
    printf ("prst_polygonMode : %d | ", prst_polygonMode);
    printf ("prst_fov : %f | ", prst_fov);
    printf ("prst_size : %f | ", prst_size);
    printf ("\n");
  }
  if (key == 'r') { // Reset
    prst_alpha = 0.0F;
    prst_beta = 0.0F;
    prst_animation = 0.0F;
    prst_bufferBitMode = 0;
    prst_polygonMode = 0;
    prst_animationSpeed = 16;
    prst_rotationSpeed = 0;
    prst_manualSpeed = 3.0F;
    prst_xMouse = 0;
    prst_yMouse = 0;
    prst_fov = 0.5;
    prst_size = 1.0F;
    prst_nbPolygon = 16;
    res = true;
  }
  return res;
}

/*void keyboard (unsigned char key, int x, int y) {
  printf ("K  %d %4c %4d %4d\n", key, key, x, y);
  
  stdKeyboard (key, x, y);
  
  else if (key == 'B') { // Champs de vue
    if (fov < 5) {
      printf ("fov : %f\n", fov);
      prst_fov += 0.05;
      reshape (wTx, wTy);
    }
  }
  else if (key == 'b') {
    if (fov > 0.01) {
      printf ("fov : %f\n", fov);
      prst_fov -= 0.05;
      reshape (wTx, wTy);
    }
  }
  else if (key == 'N') { // Taille / Zoom
    if (size_v < 10) {
      printf ("size_v : %f\n", size_v);
      size_v += 0.1F;
    }
  }
  else if (key == 'n') {
    if (size_v > 0.011) {
      printf ("size_v : %f\n", size_v);
      size_v -= 0.1F;
    }
  }
  else if (key == 'M') { // Nombre Polygones
    if (nbPolygon_v < 1024) {
      nbPolygon_v++;
    }
  }
  else if (key == 'm') {
    if (nbPolygon_v > 3) {
      nbPolygon_v--;
    }
  }
  else if (key == ' ') { // Scène
    if (sceneId < 3) {
      sceneId++;
    }
    else {
      sceneId = 0;
    }
  }
  else if (key == 'r') { // Reset
    alpha = 0.0F;
    beta = 0.0F;
    animation_v = 0.0F;
    pupil_A_v = 0.0F;
    pupil_B_v = 0.0F;
    bufferBitMode = 0;
    polygonMode = 0;
    animationSpeed = 16;
    rotationSpeed = 0;
    manualSpeed = 3.0F;
    xMouse = 0;
    yMouse = 0;
    fov = 0.5;

    size_v = 1.0F;
    nbPolygon_v = 16;
  }
  else if (key == 0X0D) { // Entrée - Pause Animation
    printf ("Animation\n");
    if (animated) {
      glutIdleFunc (NULL);
      animated = false;
    }
    else {
      glutIdleFunc (idle);
      animated = true;
    }
  }
  else if (key == 0x7f) { // Vitesse de la Rotation
    rotationSpeed--;
    printf ("New Rotation Speed : %d\n", rotationSpeed);
  }
  else if (key == 0X1B) { // Échap - Sortie
    exit (0);
  }
  glutPostRedisplay ();
}*/
