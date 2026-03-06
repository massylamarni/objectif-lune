#include <stdlib.h>
#include <stdio.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>


/* Variables globales                           */

static int wTx = 480;              // Resolution horizontale de la fenetre
static int wTy = 480;              // Resolution verticale de la fenetre
static int wPx = 50;               // Position horizontale de la fenetre
static int wPy = 50;               // Position verticale de la fenetre
static bool sensaf1 = true;
static bool sensaf2 = true;
static bool sensab = true;
static bool sensac = true;
static float anglef1 = 0.0F;
static float anglef2 = 0.0F;
static float angleb = 0.0F;
static float anglec = 0.0F;
static float alpha = 0.0F;
static float beta = 0.0F;
static float speed = 1.0F;
static bool isFill = true;
static int anim = 1;
static bool leftClick = false;
static bool rotationX = true;
static int mouseX = 0;
static int mouseY = 0;
static int faceLong = 64;
static int faceLat = 90;
static bool depthTest = true;
static bool lighting = true;
static bool light1 = true;
static float pixCol = 1.0F / 255.0F;
static float blanc[4] = { pixCol*247,pixCol*247,pixCol*247,1.0F };
static float violet_fs[4] = { pixCol*115,pixCol*115,pixCol*198,1.0F };
static float violet_ls[4] = { pixCol*115,pixCol*115,pixCol*198,1.0F };
static float violet_fc[4] = { pixCol * 175,pixCol * 178,pixCol * 216,1.0F };
static float jaune[4] = { pixCol * 228,pixCol * 186,pixCol * 54,1.0F };
static float posl[4] = { 0.0F,0.0F,0.0F,1.0F };
static float posl0[4] = { 0.0F,0.0F,1.0F,0.0F };
static float shinines[] = { 100.0F };
static float noir[4] = { 0.0F,0.0F,0.0F,1.0F };
static float no_shinines[] = { 0.0F };
static float col_light0[4] = { 0.8F,0.8F,0.8F,1.0F };


/* Fonction d'initialisation des parametres     */
/* OpenGL ne changeant pas au cours de la vie   */
/* du programme                                 */

static void init(void) {
  glEnable(GL_LIGHTING); // Le calcul d'illumination est activé
  glEnable(GL_LIGHT0); // Une lumière activé
  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST); // L'élimination des parties cachés est activé
  glEnable(GL_NORMALIZE);
  glEnable(GL_CULL_FACE);
}

/* Scene dessinee   
*/

static void mySolidCylindre(float hauteur, float rayon, int ns) {
    glPushMatrix();
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= ns; i++) {
        double angle = i * 2.0 * M_PI / ns;
        float cs = (float)cos(angle);
        float sn = (float)sin(angle);
        glNormal3f(cs, 0, sn);
        glVertex3f(cs * rayon, -hauteur / 2, sn * rayon);
        glVertex3f(cs * rayon, hauteur / 2, sn * rayon);
    }
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, 1.0F, 0);
    glVertex3f(0, hauteur / 2, 0);
    for (int i = ns; i >=0; i--) {
        double angle = i * 2.0 * M_PI / ns;
        float cs = (float)cos(angle);
        float sn = (float)sin(angle);
        glVertex3f(cs * rayon, hauteur / 2, sn * rayon);
    }
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, -1.0F, 0);
    glVertex3f(0, -hauteur / 2, 0);
    for (int i = 0; i <= ns; i++) {
        double angle = i * 2.0 * M_PI / ns;
        float cs = (float)cos(angle);
        float sn = (float)sin(angle);
        glVertex3f(cs * rayon, -hauteur / 2, sn * rayon);
    }
    glEnd();
    glPopMatrix();
}

static void funecireCorps(float hauteur, float rayonHaut, float rayonBas, int ns) {
    glPushMatrix();
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= ns; i++) {
        double angle = i * 2.0 * M_PI / ns;
        float cs = (float)cos(angle);
        float sn = (float)sin(angle);
        glNormal3f(cs, 0, sn);
        glVertex3f(cs * rayonBas, -hauteur / 2, sn * rayonBas);
        glVertex3f(cs * rayonHaut, hauteur / 2, sn * rayonHaut);
    }
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, 1.0F, 0);
    glVertex3f(0, hauteur / 2, 0);
    for (int i = ns; i >=0; i--) {
        double angle = i * 2.0 * M_PI / ns;
        float cs = (float)cos(angle);
        float sn = (float)sin(angle);
        glVertex3f(cs * rayonHaut, hauteur / 2, sn * rayonHaut);
    }
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, -1.0F, 0);
    glVertex3f(0, -hauteur / 2, 0);
    for (int i = 0; i <= ns; i++) {
        double angle = i * 2.0 * M_PI / ns;
        float cs = (float)cos(angle);
        float sn = (float)sin(angle);
        glVertex3f(cs * rayonBas, -hauteur / 2, sn * rayonBas);
    }
    glEnd();
    glPopMatrix();
}

static void funecireBase(float hauteur, float rayon, float tailleP, int ns, int np) {
    glPushMatrix();
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= ns; i++) {
        double angle = i * 2.0 * M_PI / ns;
        float cs = (float)cos(angle);
        float sn = (float)sin(angle);
        glNormal3f(cs + tailleP*(float)sin(angle*np), 0, sn + tailleP*(float)sin(angle*np));
        glVertex3f(cs * (rayon + tailleP*(float)sin(angle*np)), -hauteur / 2, sn * (rayon + tailleP*(float)sin(angle*np)));
        glVertex3f(cs * (rayon + tailleP*(float)sin(angle*np)), hauteur / 2, sn * (rayon + tailleP*(float)sin(angle*np)));
    }
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, 1.0F, 0);
    glVertex3f(0, hauteur / 2, 0);
    for (int i = ns; i >=0; i--) {
        double angle = i * 2.0 * M_PI / ns;
        float cs = (float)cos(angle);
        float sn = (float)sin(angle);
        glVertex3f(cs * (rayon + tailleP*(float)sin(angle*np)), hauteur / 2, sn * (rayon + tailleP*(float)sin(angle*np)));
    }
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, -1.0F, 0);
    glVertex3f(0, -hauteur / 2, 0);
    for (int i = 0; i <= ns; i++) {
        double angle = i * 2.0 * M_PI / ns;
        float cs = (float)cos(angle);
        float sn = (float)sin(angle);
        glVertex3f(cs * (rayon + tailleP*(float)sin(angle*np)), -hauteur / 2, sn * (rayon + tailleP*(float)sin(angle*np)));
    }
    glEnd();
    glPopMatrix();
}

static float calculVariation(int i, int ns){
        int nvar = 0;
        if ((float)i/ns<0.10){
          return 0.12F;
        }
        if ((float)i/ns>=0.10 && (float)i/ns<0.175 ){
          nvar = i-ns*0.10;
          return 0.12F-0.12F*((float)nvar/(ns*(0.175-0.10)))*((float)nvar/(ns*(0.175-0.10)));
        }
        if ((float)i/ns>=0.175 && (float)i/ns<0.25 ){
          nvar = i-ns*0.175;
          return 0.17F*sqrt((float)nvar/(ns*(0.25-0.175)));
        }
        if ((float)i/ns>=0.25 && (float)i/ns<0.30 ){
          nvar = i-ns*0.25;
          return 0.17F-0.01F*((float)nvar/(ns*(0.30-0.25)))*((float)nvar/(ns*(0.30-0.25)));
        }
        if ((float)i/ns>=0.30 && (float)i/ns<0.35 ){
          nvar = i-ns*0.30;
          return 0.17F+0.04F*sqrt((float)nvar/(ns*(0.35-0.30)))-0.01F;
        }
        if ((float)i/ns>=0.35 && (float)i/ns<0.45 ){
          nvar = i-ns*0.35;
          return 0.2F-0.08F*((float)nvar/(ns*(0.45-0.35)))*((float)nvar/(ns*(0.45-0.35)));
        }
        if ((float)i/ns>=0.42 && (float)i/ns<0.50 ){
          return 0.12F;
        }
        if ((float)i/ns>=0.50 && (float)i/ns<0.6 ){
          nvar = i-ns*0.50;
          return 0.12F+0.08F*sqrt((float)nvar/(ns*(0.6-0.50)));
        }
        if ((float)i/ns>=0.6 && (float)i/ns<0.75 ){
          nvar = i-ns*0.6;
          return 0.20F-0.06F*((float)nvar/(ns*(0.75-0.6)))*((float)nvar/(ns*(0.75-0.6)));
        }
        if ((float)i/ns>=0.75 && (float)i/ns<0.8 ){
          nvar = i-ns*0.75;
          return 0.14F+0.04F*sqrt((float)nvar/(ns*(0.8-0.75)));
        }
        if ((float)i/ns>=0.8 && (float)i/ns<1.1 ){
          nvar = i-ns*0.8;
          return 0.18F-0.06F*((float)nvar/(ns*(1.0-0.8)))*((float)nvar/(ns*(1.0-0.8)));
        }
        return 0.0F;
}

static void cheveuxFunecire(float hauteur, float rayon, int ns) {
    glPushMatrix();
    glBegin(GL_QUAD_STRIP);
    float variationH = 0.0F;
    for (int i = 0; i <= ns; i++) {
        double angle = i * 2.0 * M_PI / ns;
        float cs = (float)cos(angle);
        float sn = (float)sin(angle);
        variationH = calculVariation(i,ns);
        
        glNormal3f(cs, 0, sn);
        glVertex3f(cs * rayon, -hauteur / 2 - variationH, sn * rayon);
        glVertex3f(cs * rayon, hauteur / 2, sn * rayon);
    }
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, 1.0F, 0);
    glMaterialfv(GL_FRONT,GL_SPECULAR,violet_fs);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,violet_fs);
    glMaterialfv(GL_FRONT,GL_SHININESS,shinines);
    glVertex3f(0, hauteur / 2, 0);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,blanc);
    for (int i = ns; i >=0; i--) {
        double angle = i * 2.0 * M_PI / ns;
        float cs = (float)cos(angle);
        float sn = (float)sin(angle);
        glVertex3f(cs * rayon, hauteur / 2, sn * rayon);
    }
    glEnd();
    glMaterialfv(GL_FRONT,GL_SPECULAR,noir);
    glMaterialfv(GL_FRONT,GL_SHININESS,no_shinines);
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, -1.0F, 0);
    glVertex3f(0, -hauteur / 2- 0.2F, 0);
    for (int i = 0; i <= ns; i++) {
        double angle = i * 2.0 * M_PI / ns;
        float cs = (float)cos(angle);
        float sn = (float)sin(angle);
        variationH = calculVariation(i,ns);
        glVertex3f(cs * rayon, -hauteur / 2 - variationH, sn * rayon);
    }
    glEnd();
    glPopMatrix();
}

static void funecire(void) {
  glPushMatrix();
  glPushMatrix();
  glRotatef(anglec, 0.0F, 0.0F, 1.0F);
  glPushMatrix();
  glTranslatef(0, 0.25F, 0);
  glRotatef(270.0F, 1.0F, 0, 0);
  glRotatef(anglef1, 1.0F, 0.0F, 0.0F);
  glRotatef(anglef2, 0.0F, 1.0F, 0.0F);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, violet_fs);
  glutSolidCone(0.1F, 0.3F, faceLong, faceLat);
  glutSolidSphere(0.095F, faceLong, faceLat);
  glPopMatrix();
  glDisable(GL_DEPTH_TEST);
  glPushMatrix();
  glTranslatef(0, 0.25F, 0);
  glRotatef(270.0F, 1.0F, 0, 0);
  glRotatef(anglef1, 1.0F, 0.0F, 0.0F);
  glRotatef(anglef2, 0.0F, 1.0F, 0.0F);
  glLightfv(GL_LIGHT1, GL_POSITION, posl);
  glLightfv(GL_LIGHT1, GL_SPECULAR, violet_ls);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, violet_ls);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, violet_fc);
  glutSolidSphere(0.045F, faceLong, faceLat);
  glutSolidCone(0.05F, 0.15F, faceLong, faceLat);
  glPopMatrix();
  glEnable(GL_DEPTH_TEST);
  glPushMatrix();
  glRotatef(30.0F, 0, 1.0F, 0);
  glTranslatef(0, 0, 0.175F);
  glRotatef(90.0F, 1.0F, 0, 0);
  glScalef(1.0F, 1.0F, 1.3F);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, jaune);
  mySolidCylindre(0.01F, 0.025F, faceLong);
  glPopMatrix();
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, blanc);
  funecireCorps(0.4F, 0.2F, 0.15F, faceLong);
  glPushMatrix();
  glTranslatef(0, -0.075F, 0.17F-0.005F);
  glutSolidSphere(0.03F, faceLong, faceLat);
  glPopMatrix();
  glPushMatrix();
  glTranslatef(0.175F, 0, 0);
  glRotatef(90.0F, 0, 0, 1.0F);
  glRotatef(angleb, 0.0F, 0.0F, 1.0F);
  mySolidCylindre(0.2F, 0.02F, faceLong);
  glRotatef(90.0F, 0, 0, -1.0F);
  glTranslatef(0.1F, 0, 0);
  glutSolidSphere(0.02F, faceLong, faceLat);
  glPopMatrix();
  glPushMatrix();
  glTranslatef(-0.175F, 0, 0);
  glRotatef(-90.0F, 0, 0, 1.0F);
  glRotatef(-angleb, 0.0F, 0.0F, 1.0F);
  mySolidCylindre(0.2F, 0.02F, faceLong);
  glRotatef(-90.0F, 0, 0, -1.0F);
  glTranslatef(-0.1F, 0, 0);
  glutSolidSphere(0.02F, faceLong, faceLat);
  glPopMatrix();
  glTranslatef(0, 0.18F, 0);
  cheveuxFunecire(0.05F, 0.22F, 200);
  glPopMatrix();
  glPushMatrix();
  glTranslatef(0, -0.2F, 0);
  funecireBase(0.04F, 0.24F, 0.015F, faceLong, 6);
  glPopMatrix();
  glPopMatrix();
}

/* Fonction executee lors d'un rafraichissement */
/* de la fenetre de dessin                      */

static void display(void) {
    if (depthTest) {
        glEnable(GL_DEPTH_TEST);
  }
    else {
        glDisable(GL_DEPTH_TEST);
    }
    if (lighting) {
        glEnable(GL_LIGHTING);
    }
    else {
        glDisable(GL_LIGHTING);
    }
    if (light1) {
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
    }
    else {
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHT1);
    }
  printf("D\n");
  glClearColor(0.8F,0.8F,0.8F,1.0F);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glPushMatrix();
  glPolygonMode(GL_FRONT, (isFill) ? GL_FILL : GL_LINE);
  glRotatef(alpha, 1.0F, 0.0F, 0.0F);
  glLightfv(GL_LIGHT0, GL_POSITION, posl0);
  glRotatef(beta, 0.0F, 1.0F, 0.0F);
  glScalef(2.0F, 2.0F, 2.0F);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, col_light0);
  funecire();
  glPopMatrix();
  glFlush();
  glutSwapBuffers();
  int error = glGetError();
  if ( error != GL_NO_ERROR )
    printf("Attention erreur %d\n",error);
}

/* Fonction executee lors d'un changement       */
/* de la taille de la fenetre OpenGL            */

static void reshape(int wx,int wy) {
  printf("R\n");
  wTx = wx; 
  wTy = wy; 
  glViewport(0,0,wx,wy); 
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0); 
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

// --- GESTION DES EVENEMENTS --- 

/* Fonction executee lorsqu'aucun evenement     */
/* n'est en file d'attente                      */

static void idle1(void) {
  printf("I\n");
  if (sensaf1){
    anglef1+= 0.2F*speed;
    if (anglef1>5.0F){
      sensaf1= false;
    }
  }else{
    anglef1-= 0.2F*speed;
    if (anglef1<-5.0F){
      sensaf1= true;
    }
  }
  if (sensaf2){
    anglef2+= 0.15F*speed;
    if (anglef2>5.0F){
      sensaf2= false;
    }
  }else{
    anglef2-= 0.15F*speed;
    if (anglef2<-5.0F){
      sensaf2= true;
    }
  }
  if (sensab){
    angleb+= 0.5F*speed;
    if (angleb>30.0F){
      sensab= false;
    }
  }else{
    angleb-= 0.5F*speed;
    if (angleb<-30.0F){
      sensab= true;
    }
  }
  if (sensac){
    anglec+= 0.05F*speed;
    if (anglec>1.5F){
      sensac= false;
    }
  }else{
    anglec-= 0.01F*speed;
    if (anglec<-1.5F){
      sensac= true;
    }
  }
  glutPostRedisplay();
}



/* Fonction executee lors de l'appui            */
/* d'une touche alphanumerique du clavier       */

static void keyboard(unsigned char key,int x,int y) {
  printf("K  %4c %4d %4d\n",key,x,y);
  switch (key) {
      case 0x1B:
          exit(0);
          break;
      case 0x0D: 
          anim = !anim;
          glutIdleFunc((anim) ? idle1 : NULL);
          break;
      case ' ':
          isFill = !isFill;
          glutPostRedisplay();
          break;
      case 'n':
          speed -= 0.5;
          if (speed <= 0) {
              speed = 0.5;
          }
          glutPostRedisplay();
          break;
      case 'N':
          speed -= 0.5;
          if (speed <= 0) {
              speed = 0.5;
          }
          glutPostRedisplay();
          break;
      case 'm':
          speed += 0.5;
          if (speed > 16) {
              speed = 16;
          }
          glutPostRedisplay();
          break;
      case 'M':
          speed += 0.5;
          if (speed > 13) {
              speed = 13;
          }
          glutPostRedisplay();
          break;
      case 'f':
          depthTest = !depthTest;
          glutPostRedisplay();
          break;
      case 'L':
          lighting = !lighting;
          glutPostRedisplay();
          break;
      case 'l':
          light1 = !light1;
          glutPostRedisplay();
          break;
  }
  
}

/* Fonction executee lors de l'appui            */
/* d'une touche speciale du clavier :           */
/*   - touches de curseur                       */
/*   - touches de fonction                      */

static void special(int specialKey,int x,int y) {
  printf("S  %4d %4d %4d\n",specialKey,x,y);
}

/* Fonction executee lors de l'utilisation      */
/* de la souris sur la fenetre                  */

static void mouse(int button, int state, int x, int y) {
    printf("M  %4d %4d %4d %4d\n", button, state, x, y);
    if (button == 2 && state == 0) {
        rotationX = !rotationX;
    }
    else {
        leftClick = button == 0;
        mouseX = x;
        mouseY = y;
    }
}

/* Fonction executee lors du passage            */
/* de la souris sur la fenetre                  */
/* avec un bouton presse                        */

static void mouseMotion(int x, int y) {
    printf("MM %4d %4d\n", x, y);
    if (leftClick) {
        beta += mouseX - x;
        alpha += mouseY - y;
        mouseX = x;
        mouseY = y;
        glutPostRedisplay();
    }
}

/* Fonction executee lors du passage            */
/* de la souris sur la fenetre                  */
/* sans bouton presse                           */

static void passiveMouseMotion(int x,int y) {
  printf("PM %4d %4d\n",x,y);
}

/* Fonction exécutée automatiquement            */
/* lors de l'exécution de la fonction exit()    */

static void clean(void) {
  printf("Bye\n");
}

// ------------------------

/* Fonction principale                          */

int main(int argc,char **argv) {

  atexit(clean); // exécution d'une fonction (static void clean(void)) lorsque l'application est interrompue par exécution de la fonction standard void exit(int)

  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
  glutInitWindowSize(wTx,wTy);
  glutInitWindowPosition(wPx,wPy);
  glutCreateWindow("Une animation"); // création de la fenêtre de visualisation
  init();
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(special);
  glutMouseFunc(mouse);
  glutMotionFunc(mouseMotion);
  //glutPassiveMotionFunc(passiveMouseMotion);
  glutReshapeFunc(reshape);
  glutIdleFunc(idle1);
  //glutIdleFunc(NULL);
  glutDisplayFunc(display); // affichage de la fenêtre de visualisation
  glutMainLoop(); // lancement de la boucle infinie de gestion des événements
  return(0);
}
