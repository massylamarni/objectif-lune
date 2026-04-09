#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#include "custom_preset.h"


/* Variables globales                           */

float red[] = { 1.0F, 0.0F, 0.0F, 1.0F };
float black[] = { 1.0F, 1.0F, 1.0F, 1.0F };
float orange[] = { 1.0F, 0.33F, 0.0F, 1.0F };
float white[] = { 1.0F, 1.0F, 1.0F, 1.0F };
int n_lat=40;
int n_long=20;
int tremblement=0;
float explosion_size=0.0F;
float saturation=0.0F;
float anim_saturation=0.0F;
float anim_explosion=0.0F;
float anim_reactor_offset [] = { 0.0F, 5.0F, 10.0F, 15.0F, 20.0F, 25.0F, 30.0F, 35.0F, 40.0F, 45.0F, 50.0F, 55.0F, 60.0F, 65.0F, 70.0F, 75.0F, 80.0F, 85.0F, 90.0F, 95.0F };


/* Fonction d'initialisation des parametres     */
/* OpenGL ne changeant pas au cours de la vie   */
/* du programme                                 */

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

void fummee_idle () {
    for (int i = 0 ; i < 20 ; i++) {
      if (prst_animation - anim_reactor_offset [i] > 75) {
        anim_reactor_offset [i] = prst_animation;
      }
    }
  }

void fummee_anim (float power) { /* [0.0F - 1.0F]*/
    if (0.15F < power) {
      glPushMatrix ();
      if (power > 1.0F) power = 1.0F;
      glScalef (power, power, power);
      for (int i = 0 ; i < 20 ; i++) {
        if (prst_animation - anim_reactor_offset [i] < power * 75 && prst_animation - anim_reactor_offset [i] >= 0) {
          glPushMatrix ();
           
          glRotatef ((i * 108.0F), 0.0F, 1.0F, 0.0F);
          glTranslatef (0.0015F * (prst_animation - anim_reactor_offset [i]), -0.04F * (prst_animation - anim_reactor_offset [i]), (float) i * 0.0005F);
          if ((i * 108)%360 > 90 && (i * 108)%360 < 270) glScalef (1.0F, 1.0F, 2.0F);
          else glScalef (2.0F, 1.0F, 1.0F);
          glutSolidSphere (0.004F * (anim_reactor_offset [i] - prst_animation + 75), 8, 8);
          
          glPopMatrix ();
        }
      }
        glPopMatrix ();
    }
  }

static float resteDivf(float dividende, float diviseur) {
  while (dividende>= diviseur) {
    dividende-=diviseur;
  }
  return dividende;
}

static void ExplosionSphere(int nb_frag, float rayon_int, float rayon_ext) {
    for(int i=1; i<=nb_frag;i++){
      glPushMatrix();
      glRotatef(81.0F*i*rayon_ext*nb_frag,1.0F,0.0F,0.0F);
      glRotatef(26.0F*i*rayon_ext*nb_frag,0.0F,1.0F,0.0F);
      glRotatef(42.0F*i*rayon_ext*nb_frag,0.0F,0.0F,1.0F);
      glTranslatef(0.0F,(resteDivf(0.1181F*i,rayon_ext-rayon_int)+rayon_int)*explosion_size,0.0F);
      glutSolidSphere(0.07F*explosion_size,3,3);
      glPopMatrix();
    }
}

static void Explosion(void) {
  glPushMatrix();
  float col_explosion_rouge[] = { 1.0F-(saturation*0.9F), 0.0F+(saturation*0.1F), 0.0F+(saturation*0.1F), 1.0F };
  float col_explosion_orange[] = { 1.0F-(saturation*0.8F), 0.33F-(saturation*0.13F), 0.0F+(saturation*0.2F), 1.0F };
  float col_explosion_jaune[] = { 1.0F-(saturation*0.7F), 1.0F-(saturation*0.7F), 0.0F+(saturation*0.3F), 1.0F };
  float col_explosion_noir[] = { 0.0F, 0.0F, 0.0F, 1.0F };
  glPushMatrix();
  glScalef(1.2F, 1.2F, 1.2F);
  glTranslatef(0.0F,0.5F*explosion_size,0.0F);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, col_explosion_jaune);
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, col_explosion_jaune);
  ExplosionSphere(40, 0.075F, 0.125F);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, col_explosion_orange);
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, col_explosion_orange);
  ExplosionSphere(41, 0.21F, 0.25F);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, col_explosion_rouge);
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, col_explosion_rouge);
  ExplosionSphere(42, 0.335F, 0.375F);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, col_explosion_noir);
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, col_explosion_noir);
  ExplosionSphere(44, 0.46F, 0.5F);
  glPopMatrix();
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, col_explosion_noir);
  glPushMatrix();
  glRotatef(90.0F, 1.0F, 0.0F, 0.0F);
  for(int i=1; i<=20;i++){
    glRotatef(360.0F/20.0F, 0.0F, 0.0F, 1.0F);
    fummee_anim(explosion_size);
  }
  glPopMatrix();
  glPopMatrix();
}

void scene (void) {
  glPushMatrix();
  
  Explosion();
  
  glPopMatrix();
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

void idle2 (void) {
  printf ("I\n");
  anim_saturation += (float) prst_animationSpeed / 120.0F;
  prst_animation += ((float) prst_animationSpeed) / 5.0F;
  fummee_idle ();
  tremblement+=4;
  saturation=sqrt(anim_saturation);
  if (anim_saturation>1.0F){
    saturation=1.0F;
    glutIdleFunc (NULL);
  }
  glMaterialfv (GL_FRONT, GL_DIFFUSE,  red);
  glMaterialfv (GL_BACK, GL_DIFFUSE,  red);
  glutPostRedisplay ();
}

void idle (void) {
  printf ("I\n");
  anim_explosion += (float) prst_animationSpeed / 240.0F;
  prst_animation += ((float) prst_animationSpeed) / 5.0F;
  fummee_idle ();
  tremblement+=8;
  if (anim_explosion<0.9F/7.0F){
    explosion_size=anim_explosion*7.0F;
  }else{
    explosion_size=anim_explosion*0.1F+0.9F;
  }
  if (explosion_size>1.0F){
    glutIdleFunc (idle2);
  }
  glMaterialfv (GL_FRONT, GL_DIFFUSE,  red);
  glMaterialfv (GL_BACK, GL_DIFFUSE,  red);
  glutPostRedisplay ();
}



 /* Fonction exécutée lors de l'appui            */ 
 /* d'une touche alphanumérique du clavier       */ 

void keyboard (unsigned char key, int x, int y) {
  printf ("K  %d %4c %4d %4d\n", key, key, x, y);
  
  if (stdKeyboard (key, x, y)) {
    reshape (prst_wTx, prst_wTy);
  }
  
  keyboardAssistIntLoop (&prst_sceneId, key, 'M', 'm', 0, 3);
  
  printf("Bool %d\n",
  keyboardAssistFloatProportional (&prst_rotationSpeed, key, (char) GLUT_KEY_INSERT, 0x7f, -3600.0F, 3600.0F, 0.05F, 0.05F)
  );
  if (keyboardAssistBool (&prst_animated, key, 0X0D)) { // Entrée - Pause Animation
    printf ("Animation\n");    
    if (prst_animated) {
      glutIdleFunc (NULL);
    }
    else {
      prst_animationSpeed=1;
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
  
  
  glutKeyboardFunc (keyboard);
  glutSpecialFunc (special);
  glutMouseFunc (mouse);
  glutMotionFunc (mouseMotion);
  //glutPassiveMotionFunc (passiveMouseMotion);
  glutReshapeFunc (reshape);
  glutIdleFunc (idle);
  glutIdleFunc (NULL);
  glutDisplayFunc (display);
  glutMainLoop ();
  return (0); // Won't be reach cause the normal way to stop is exit the MainLoop
}
