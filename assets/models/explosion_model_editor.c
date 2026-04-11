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

#include "custom_preset.h"
#include "explosion.h"

 /* Variables globales                           */

float pos_directionnal[] = { 1.0F, 0.0F, 0.0F, 0.0F };
float white[] = { 1.0F, 1.0F, 1.0F, 1.0F };
float grey[] = { 0.5F, 0.5F, 0.5F, 0.5F };

float anim_win_offset_me = 0.0F; // me -> model editor // doivent être gérées par le jeu
float anim_reactor_offset_me [] = { 0.0F, 10.0F, 20.0F, 30.0F, 40.0F, 50.0F, 60.0F, 70.0F, 80.0F, 90.0F };
bool win_value_me = false;
bool reactor_activity_me = false;
float rotation_power_me = 0.0F;
float rotation_direction_me = 0.0F;

 /* Fonction d'initialisation des paramètres     */
 /* OpenGL ne changeant pas ou peu au cours de   */
 /* la vie du programme                          */

void init (void) {
  glEnable (GL_LIGHTING);
  glEnable (GL_LIGHT0);
  glEnable (GL_LIGHT1);
  //glDisable (GL_LIGHT0);
  
  glLightfv (GL_LIGHT0, GL_DIFFUSE,  white);
  glLightfv (GL_LIGHT0, GL_SPECULAR, white);
  glLightfv (GL_LIGHT0, GL_AMBIENT,  white);
  
  glLightfv (GL_LIGHT1, GL_DIFFUSE,  grey);
  glLightfv (GL_LIGHT1, GL_SPECULAR, grey);
  glLightfv (GL_LIGHT1, GL_AMBIENT,  grey);
  
  
  glColorMaterial (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  
  glDepthFunc (GL_LESS);
  glEnable (GL_DEPTH_TEST);
  glEnable (GL_NORMALIZE);
  glClearColor (0.1F, 0.3F, 0.2F, 1.0F);
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

void scene (void) {
  glPushMatrix ();
  
  glTranslatef (0.0F,-1.0F, 0.0F);
  
  glPushMatrix ();
  glRotatef (prst_animation / 10.0F, 0.0F, 1.0F, 0.5F);
  glLightfv (GL_LIGHT0, GL_POSITION, pos_directionnal); // Sun
  glRotatef (prst_animation / 42.1F, 0.0F, 0.2F, 1.0F);
  glLightfv (GL_LIGHT1, GL_POSITION, pos_directionnal); // Moon
  glPopMatrix ();

  explosion_model();
  
  glPopMatrix ();
}

 /* Fonction executee lors d'un rafraichissement */ 
 /* de la fenetre de dessin                      */ 

void display (void) {
 /* Préparation                                  */
  //printf ("D\n");
  
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
  explosion_idle (prst_animationSpeed);
  glutPostRedisplay ();
}

 /* Fonction exécutée lors de l'appui            */ 
 /* d'une touche alphanumérique du clavier       */ 

void keyboard (unsigned char key, int x, int y) {
  printf ("K  %d %4c %4d %4d\n", key, key, x, y);
  
  if (stdKeyboard (key, x, y)) {
    reshape (prst_wTx, prst_wTy);
  }
  
  if (keyboardAssistBool (&prst_animated, key, 0X0D)) { // Entrée - Pause Animation    
    if (prst_animated) {
      glutIdleFunc (NULL);
    }
    else {
      glutIdleFunc (idle);
      start_explosion_animation();
    }
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
  
}

 /* Fonction executee lors du passage            */ 
 /* de la souris sur la fenetre                  */ 
 /* avec un bouton presse                        */ 

void mouseMotion (int x, int y) {
  printf ("MM %4d %4d\n", x, y);
  prst_beta += x - prst_xMouse;
  prst_alpha += y - prst_yMouse;
  
  
  
  glutPostRedisplay ();
}

 /* Fonction executee lors du passage            */ 
 /* de la souris sur la fenetre                  */ 
 /* sans bouton presse                           */ 

void passiveMouseMotion (int x, int y) {
  //printf ("PM %4d %4d\n", x, y);
  
  
  glutPostRedisplay (); 
}

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
  glutCreateWindow ("Explosion");
  init ();
  
  
  glutKeyboardFunc (keyboard);
  glutSpecialFunc (special);
  glutMouseFunc (mouse);
  glutMotionFunc (mouseMotion);
  glutPassiveMotionFunc (passiveMouseMotion);
  glutReshapeFunc (reshape);
  glutIdleFunc (NULL);
  //glutIdleFunc (NULL);
  glutDisplayFunc (display);
  glutMainLoop ();
  return (0); // Won't be reach cause the normal way to stop is exit the MainLoop
}
