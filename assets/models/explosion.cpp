#include "explosion.h"

static render::model_proprty mp = render::init_model_property();

/* Variables globales                           */

static float red[] = {1.0F, 0.0F, 0.0F, 1.0F};
static float black[] = {1.0F, 1.0F, 1.0F, 1.0F};
static float orange[] = {1.0F, 0.33F, 0.0F, 1.0F};
static float white[] = {1.0F, 1.0F, 1.0F, 1.0F};
static int n_lat = 40;
static int n_long = 20;
static int tremblement = 0;
static float explosion_size = 0.0F;
static float saturation = 0.0F;
static float anim_saturation = 0.0F;
static float anim_explosion = 0.0F;
static float anim_reactor_offset[] = {0.0F,  5.0F,  10.0F, 15.0F, 20.0F, 25.0F, 30.0F,
                               35.0F, 40.0F, 45.0F, 50.0F, 55.0F, 60.0F, 65.0F,
                               70.0F, 75.0F, 80.0F, 85.0F, 90.0F, 95.0F};

void fummee_idle() {
  for (int i = 0; i < 20; i++) {
    if (mp.ds.animation_total_speed - anim_reactor_offset[i] > 75) {
      anim_reactor_offset[i] = mp.ds.animation_total_speed;
    }
  }
}

void fummee_anim(float power) { /* [0.0F - 1.0F]*/
  if (0.15F < power) {
    glPushMatrix();
    if (power > 1.0F)
      power = 1.0F;
    glScalef(power, power, power);
    for (int i = 0; i < 20; i++) {
      if (mp.ds.animation_total_speed - anim_reactor_offset[i] < power * 75 &&
          mp.ds.animation_total_speed - anim_reactor_offset[i] >= 0) {
        glPushMatrix();

        glRotatef((i * 108.0F), 0.0F, 1.0F, 0.0F);
        glTranslatef(
            0.0015F * (mp.ds.animation_total_speed - anim_reactor_offset[i]),
            -0.04F * (mp.ds.animation_total_speed - anim_reactor_offset[i]),
            (float)i * 0.0005F);
        if ((i * 108) % 360 > 90 && (i * 108) % 360 < 270)
          glScalef(1.0F, 1.0F, 2.0F);
        else
          glScalef(2.0F, 1.0F, 1.0F);
        glutSolidSphere(
            0.004F * (anim_reactor_offset[i] - mp.ds.animation_total_speed + 75),
            8, 8);

        glPopMatrix();
      }
    }
    glPopMatrix();
  }
}

float resteDivf(float dividende, float diviseur) {
  while (dividende >= diviseur) {
    dividende -= diviseur;
  }
  return dividende;
}

void ExplosionSphere(int nb_frag, float rayon_int, float rayon_ext) {
  for (int i = 1; i <= nb_frag; i++) {
    glPushMatrix();
    glRotatef(81.0F * i * rayon_ext * nb_frag, 1.0F, 0.0F, 0.0F);
    glRotatef(26.0F * i * rayon_ext * nb_frag, 0.0F, 1.0F, 0.0F);
    glRotatef(42.0F * i * rayon_ext * nb_frag, 0.0F, 0.0F, 1.0F);
    glTranslatef(0.0F,
                 (resteDivf(0.1181F * i, rayon_ext - rayon_int) + rayon_int) *
                     explosion_size,
                 0.0F);
    glutSolidSphere(0.07F * explosion_size, 3, 3);
    glPopMatrix();
  }
}

void explosion_model() {
  glPushMatrix();
  float col_explosion_rouge[] = {1.0F - (saturation * 0.9F),
                                 0.0F + (saturation * 0.1F),
                                 0.0F + (saturation * 0.1F), 1.0F};
  float col_explosion_orange[] = {1.0F - (saturation * 0.8F),
                                  0.33F - (saturation * 0.13F),
                                  0.0F + (saturation * 0.2F), 1.0F};
  float col_explosion_jaune[] = {1.0F - (saturation * 0.7F),
                                 1.0F - (saturation * 0.7F),
                                 0.0F + (saturation * 0.3F), 1.0F};
  float col_explosion_noir[] = {0.0F, 0.0F, 0.0F, 1.0F};
  glPushMatrix();
  glScalef(1.2F, 1.2F, 1.2F);
  glTranslatef(0.0F, 0.5F * explosion_size, 0.0F);
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
  for (int i = 1; i <= 20; i++) {
    glRotatef(360.0F / 20.0F, 0.0F, 0.0F, 1.0F);
    fummee_anim(explosion_size);
  }
  glPopMatrix();
  glPopMatrix();
}

static void idle2(void) {
  printf("I\n");
  anim_saturation += (float)mp.ds.animation_speed / 120.0F;
  mp.ds.animation_total_speed += ((float)mp.ds.animation_speed) / 5.0F;
  fummee_idle();
  tremblement += 4;
  saturation = sqrt(anim_saturation);
  if (anim_saturation > 1.0F) {
    saturation = 1.0F;
    glutIdleFunc(NULL);
  }
  glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
  glMaterialfv(GL_BACK, GL_DIFFUSE, red);
}

void explosion_idle(void) {
  printf("I\n");
  anim_explosion += (float)mp.ds.animation_speed / 240.0F;
  mp.ds.animation_total_speed += ((float)mp.ds.animation_speed) / 5.0F;
  fummee_idle();
  tremblement += 8;
  if (anim_explosion < 0.9F / 7.0F) {
    explosion_size = anim_explosion * 7.0F;
  } else {
    explosion_size = anim_explosion * 0.1F + 0.9F;
  }
  if (explosion_size > 1.0F) {
    //glutIdleFunc(idle2);
  }
  glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
  glMaterialfv(GL_BACK, GL_DIFFUSE, red);
}