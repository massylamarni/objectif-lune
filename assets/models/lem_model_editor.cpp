/* Modélisation d'un attérisseur spatial        */
/*                                              */
/* Projet Objectif Lune                         */

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "../../src/input/input.h"
#include "../../src/input/keyboard.h"
#include "../../src/render/renderer.h"
#include "lem.h"
#include "lem_model_editor.h"

static render::model_proprty mp = render::init_model_property();
input::InputState is = input::get_input_state();

/* Variables globales                           */

float pos_directionnal[] = {1.0F, 0.0F, 0.0F, 0.0F};

float anim_win_offset_me =
    0.0F; // me -> model editor // doivent être gérées par le jeu
float anim_reactor_offset_me[] = {0.0F,  10.0F, 20.0F, 30.0F, 40.0F,
                                  50.0F, 60.0F, 70.0F, 80.0F, 90.0F};
bool win_value_me = false;
bool reactor_activity_me = false;
float rotation_power_me = 0.0F;
float rotation_direction_me = 0.0F;

/* Fonction d'initialisation des paramètres     */
/* OpenGL ne changeant pas ou peu au cours de   */
/* la vie du programme                          */

void test_light() {
  glPushMatrix();

  float pos[] = {
      (0.001F * (is.mouse_position.x - render::SCREEN_WIDTH / 2)), 0.2F,
      (0.001F * (is.mouse_position.y - render::SCREEN_HEIGHT / 4)), 1.0F};
  glEnable(GL_LIGHT1);
  glDisable(GL_LIGHT0);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
  glLightfv(GL_LIGHT1, GL_SPECULAR, white);
  glLightfv(GL_LIGHT1, GL_POSITION, pos);

  material_white();
  glBegin(GL_LINES);
  glVertex3f((0.001F * (is.mouse_position.x - render::SCREEN_WIDTH / 2)), 0.2F,
             (0.001F * (is.mouse_position.y - render::SCREEN_HEIGHT / 4)));
  glVertex3f(0.0F, 0.0F, 0.0F);
  glEnd();

  glTranslatef((0.001F * (is.mouse_position.x - render::SCREEN_WIDTH / 2)),
               0.2F,
               (0.001F * (is.mouse_position.y - render::SCREEN_HEIGHT / 4)));
  glutSolidSphere(0.05, 16, 16);

  glPopMatrix();
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

void lem_model(void) {
  glPushMatrix();

  glTranslatef(0.0F, -1.0F, 0.0F);

  glPushMatrix();
  glRotatef(mp.ds.animation_total_speed / 10.0F, 0.0F, 1.0F, 0.5F);
  glLightfv(GL_LIGHT0, GL_POSITION, pos_directionnal); // Sun
  glRotatef(mp.ds.animation_total_speed / 42.1F, 0.0F, 0.2F, 1.0F);
  glLightfv(GL_LIGHT1, GL_POSITION, pos_directionnal); // Moon
  glPopMatrix();

  // printf("LEM Parameters : Direction %f ; Power %f\n", rotation_direction_me, rotation_power_me);
  lem(reactor_activity_me, rotation_direction_me, rotation_power_me,
      anim_win_offset_me, anim_reactor_offset_me, win_value_me,
      mp.ds.animation_total_speed, mp.ds.poly_count);

  glPopMatrix();
}
void lem_display(void) {
  // glTranslatef(0.0F, 0.0F, -5.0F);
  glTranslatef(0.0F, 0.0F, -2.5F);
  material_flame();
  glutSolidSphere(0.01F, 4, 3); // Mire
  glTranslatef(0.0F, 0.0F, -2.5F);
  // test_light ();
  glRotatef(is.mouse_delta.x, 1.0F, 0.0F, 0.0F);
  glRotatef(is.mouse_delta.y, 0.0F, 1.0F, 0.0F);
  glScalef(mp.op.scale_value, mp.op.scale_value, mp.op.scale_value);

  lem_model();
}
void lem_idle(void) {
  // printf ("I\n");
  mp.ds.animation_total_speed += ((float)mp.ds.animation_speed) / 5.0F;
  if ((mp.ds.animation_total_speed && mp.ds.animation_speed != 0) ||
      (mp.ds.is_rotation_on && mp.ds.rotation_speed != 0)) {
    is.mouse_delta.y += (float)mp.ds.rotation_speed / 10;
    // sleep (1); // Anti-Lag
    glutPostRedisplay();
  }

  if (reactor_activity_me) {
    reactor_idle(anim_reactor_offset_me, mp.ds.animation_total_speed);
  }
}

void lem_keyboard(unsigned char key, int x, int y) {
  if (key == ' ') {
    gltoggle_on_key_press(GL_LIGHT2, key, ' ');
    if (!reactor_activity_me) {
      reactor_activity_me = true;
      reactor_init(anim_reactor_offset_me, mp.ds.animation_total_speed);
    }
    glEnable(GL_LIGHT3); // TODO FIX
    glEnable(GL_LIGHT4); // TODO FIX
  } else {
    reactor_activity_me = false;
    glDisable(GL_LIGHT3); // TODO FIX
    glDisable(GL_LIGHT4); // TODO FIX
  }

  if (key == 'w') { // Active Win condition
    win_value_me = !win_value_me;
    if (win_value_me) {
      anim_win_offset_me = mp.ds.animation_total_speed;
    }
  }
}

void lem_mouse(int button, int state, int x, int y) {
  is.mouse_position.x = x;
  is.mouse_position.y = y;
  if (button == 0) {
    is.mouse_position.x = x;
    is.mouse_position.y = y;
    mp.ds.is_rotation_on = (state == 1);
  } else if (button == 2) {
    if (state == 0) {
      reactor_activity_me = true;
      for (int i = 0; i < 10; i++) {
        anim_reactor_offset_me[i] = mp.ds.animation_total_speed + (i * 10.0F);
      }
      glEnable(GL_LIGHT2);
      glEnable(GL_LIGHT3);
      glEnable(GL_LIGHT4);
    } else {
      reactor_activity_me = false;
      glDisable(GL_LIGHT2);
      glDisable(GL_LIGHT3);
      glDisable(GL_LIGHT4);
    }
  }
  rotation_update(x, y, render::SCREEN_WIDTH, render::SCREEN_HEIGHT,
                  &rotation_direction_me, &rotation_power_me);
}
void lem_mouse_motion(int x, int y) {
  is.mouse_delta.y += x - is.mouse_position.x;
  is.mouse_delta.x += y - is.mouse_position.y;
  is.mouse_position.x = x;
  is.mouse_position.y = y;
  rotation_update(x, y, render::SCREEN_WIDTH, render::SCREEN_HEIGHT,
                  &rotation_direction_me, &rotation_power_me);
}
void lem_passive_mouse_motion(int x, int y) {
  rotation_update(x, y, render::SCREEN_WIDTH, render::SCREEN_HEIGHT,
                  &rotation_direction_me, &rotation_power_me);
}
