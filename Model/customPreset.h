#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

extern int prst_wTx;                // Résolution horizontale de la fenêtre
extern int prst_wTy;                // Résolution verticale de la fenêtre
extern int prst_wPx;                // Position horizontale de la fenêtre
extern int prst_wPy;                // Position verticale de la fenêtre
extern float prst_alpha;            // Angle autour de l'axe X
extern float prst_beta;             // Angle autour de l'axe Y
extern float prst_animation;        // Compteur Animation
extern int prst_bufferBitMode;      // Mode Buffer GL
extern int prst_polygonMode;        // Mode d'affichage des polygones (faces pleines / arêtes / points)
extern int prst_polygonModeList[];
extern bool prst_animated;          // Animation
extern int prst_animationSpeed;     // Vitesse Animation
extern float prst_rotationSpeed;    // Vitesse Rotation
extern float prst_manualSpeed;      // Vitesse Camera Manuelle
extern int prst_xMouse;             // Abscisse de la souris
extern int prst_yMouse;             // Ordonnée de la souris
extern bool prst_rotation;          // Rotation automatique
extern float prst_fov;              // Champs de vue
extern float prst_size;             // Facteur Taille
extern int prst_nbPolygon;          // Nombre de Polygones
extern int prst_sceneId;            // Identifiant de scène
extern bool prst_verbose;           // Mode verbeux

bool keyboardAssistBool (bool* var, char current, char activation);

bool keyboardAssistInt  (int* var, char current, char increment, char decrement, int min_value, int max_value);

bool keyboardAssistIntLoop (int* var, char current, char increment, char decrement, int min_value, int max_value);

bool keyboardAssistFloatLinear (float* var, char current, char increment, char decrement, float min_value, float max_value, float step);

bool keyboardAssistFloatLinearLoop (float* var, char current, char increment, char decrement, float min_value, float max_value, float step);

bool keyboardAssistFloatProportional (float* var, char current, char increment, char decrement, float min_value, float max_value, float step, float step_factor);

bool keyboardAssistFloatProportionalLoop (float* var, char current, char increment, char decrement, float min_value, float max_value, float step, float step_factor);

void keyboardAssistToggle (int var, char current, char activation);

bool stdKeyboard (unsigned char key, int x, int y);

/*
void keyboard (unsigned char key, int x, int y) {
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
}
*/
