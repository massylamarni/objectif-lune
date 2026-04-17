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

bool keyboardAssistToggle (int var, char current, char activation);

bool stdKeyboard (unsigned char key, int x, int y);
