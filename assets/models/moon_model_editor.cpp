/* Modélisation d'un attérisseur spatial        */
/*                                              */
/* Projet Objectif Lune                         */

#include "../../src/render/renderer_settings.h"
#include "../../src/input/input.h"
#include "lem.h"

/* Variables globales                           */

/* Fonction d'initialisation des paramètres     */
/* OpenGL ne changeant pas ou peu au cours de   */
/* la vie du programme                          */

static render::model_proprty mp = render::init_model_property();
input::InputState is = input::get_input_state();

float pos_directionnal[] = {1.0F, 0.0F, 0.0F, 0.0F};

void scene(void) {
  glPushMatrix();

  glTranslatef(0.0F, -1.0F, 0.0F);

  glPushMatrix();
  glRotatef(mp.ds.animation_total_speed / 10.0F, 0.0F, 1.0F, 0.5F);
  glLightfv(GL_LIGHT0, GL_POSITION, pos_directionnal); // Sun
  glPopMatrix();

  glPopMatrix();
}

void display(void) {
  /* Préparation                                  */
  // printf ("D\n");

  /* Modélisation Géométrique                     */
  glPushMatrix();

  // glTranslatef(0.0F, 0.0F, -5.0F);
  glTranslatef(0.0F, 0.0F, -2.5F);
  material_flame();
  glutSolidSphere(0.01F, 4, 3); // Mire
  glTranslatef(0.0F, 0.0F, -2.5F);
  // test_light ();
  glRotatef(is.mouse_delta.x, 1.0F, 0.0F, 0.0F);
  glRotatef(is.mouse_delta.y, 0.0F, 1.0F, 0.0F);
  glScalef(mp.op.scale_value, mp.op.scale_value, mp.op.scale_value);

  scene();

  glPopMatrix();

  /* Rastérisation                                */
  glFlush();
  glutSwapBuffers();
  /* Erreurs                                      */

  int error = glGetError();
  if (error != GL_NO_ERROR)
    printf("Attention erreur %d\n", error);
}

void idle(void) {
  // printf ("I\n");
  mp.ds.animation_total_speed += ((float)mp.ds.animation_speed) / 5.0F;
  if ((mp.ds.animation_total_speed && mp.ds.animation_speed != 0) ||
      (mp.ds.is_rotation_on && mp.ds.rotation_speed != 0)) {
    is.mouse_delta.y += (float)mp.ds.rotation_speed / 10;
    // sleep (1); // Anti-Lag
    glutPostRedisplay();
  }
  /*
  if (reactor_activity_me) {
    reactor_idle (anim_reactor_offset_me, mp.ds.animation_total_speed);
  }
    */
}
