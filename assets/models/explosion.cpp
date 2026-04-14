#include "explosion.h"


/* Variables globales                           */

static int n_lat=40;
static int n_long=20;
static int animation_phase=0;
static float tremblement=0.0F;
static float explosion_size=0.0F;
static float fummee_size=0.0F;
static float saturation=0.0F;
static float anim_saturation=0.0F;
static float anim_explosion=0.0F;
static float anim_fummee=0.0F;
static float anim_fummee_offset [] = { 0.0F, 5.0F, 10.0F, 15.0F, 20.0F, 25.0F, 30.0F, 35.0F, 40.0F, 45.0F, 50.0F, 55.0F, 60.0F, 65.0F, 70.0F, 75.0F, 80.0F, 85.0F, 90.0F, 95.0F };

void fummee_idle () {
    for (int i = 0 ; i < 20 ; i++) {
      if (anim_fummee - anim_fummee_offset [i] > 75) {
        anim_fummee_offset [i] = anim_fummee;
      }
    }
  }

void fummee_anim (float power) { 
    if (0.15F < power) {
      glPushMatrix ();
      if (power > 1.0F) power = 1.0F;
      glScalef (power, power, power);
      for (int i = 0 ; i < 20 ; i++) {
        if (anim_fummee - anim_fummee_offset [i] < power * 75 && anim_fummee - anim_fummee_offset [i] >= 0) {
          glPushMatrix ();
           
          glRotatef ((i * 108.0F), 0.0F, 1.0F, 0.0F);
          glTranslatef (0.0015F * (anim_fummee - anim_fummee_offset [i]), -0.04F * (anim_fummee - anim_fummee_offset [i]), (float) i * 0.0005F);
          if ((i * 108)%360 > 90 && (i * 108)%360 < 270) glScalef (1.0F, 1.0F, 2.0F);
          else glScalef (2.0F, 1.0F, 1.0F);
          glutSolidSphere (0.004F * (anim_fummee_offset [i] - anim_fummee + 75), 8, 8);
          
          glPopMatrix ();
        }
      }
        glPopMatrix ();
    }
  }

float resteDivf(float dividende, float diviseur) {
  while (dividende>= diviseur) {
    dividende-=diviseur;
  }
  return dividende;
}

void ExplosionSphere(int nb_frag, float rayon_int, float rayon_ext) {
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

void explosion_model(void) {
  glPushMatrix();
  float col_explosion_rouge[] = { 1.0F-(saturation*0.9F), 0.0F+(saturation*0.1F), 0.0F+(saturation*0.1F), 1.0F };
  float col_explosion_orange[] = { 1.0F-(saturation*0.8F), 0.33F-(saturation*0.13F), 0.0F+(saturation*0.2F), 1.0F };
  float col_explosion_jaune[] = { 1.0F-(saturation*0.7F), 1.0F-(saturation*0.7F), 0.0F+(saturation*0.3F), 1.0F };
  float col_explosion_noir[] = { 0.0F, 0.0F, 0.0F, 1.0F };
  glPushMatrix();
  glScalef(1.2F, 1.2F, 1.2F);
  glTranslatef(0.0F,0.5F*explosion_size,0.0F);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, col_explosion_noir);
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
    fummee_anim(fummee_size);
  }
  glPopMatrix();
  glPopMatrix();
}

void start_explosion_animation () {
  animation_phase=1;
  tremblement=0.0F;
  explosion_size=0.0F;
  fummee_size=0.0F;
  saturation=0.0F;
  anim_saturation=0.0F;
  anim_explosion=0.0F;
  anim_fummee=0.0F;
}

int getExplosionPhase (){
  return animation_phase;
}

void phaseExplosion1 (float animation_time) {
  anim_explosion += animation_time * 0.33F;
  anim_fummee += animation_time * 12.0F;
  fummee_size += animation_time * 0.25F;
  fummee_idle ();
  tremblement+=8.0F;
  if (anim_explosion<0.9F/7.0F){
    explosion_size=anim_explosion*7.0F;
  }else{
    explosion_size=anim_explosion*0.1F+0.9F;
  }
  if (explosion_size>1.0F){
    animation_phase=2;
    explosion_size=1.0F;
  }
}

void phaseExplosion2 (float animation_time) {
  anim_saturation += animation_time * 0.33F;
  anim_fummee += animation_time * 5.99F;
  fummee_size += animation_time * 0.18F;
  fummee_idle ();
  tremblement+=4.0F;
  saturation=sqrt(anim_saturation);
  if (anim_saturation>1.0F){
    saturation=1.0F;
    animation_phase=3;
  }
}

void phaseExplosion3 (float animation_time) {
  anim_explosion -= animation_time * 0.25F;
  anim_fummee += animation_time * 4.0F;
  fummee_size += animation_time * 0.12F;
  fummee_idle ();
  tremblement+=2.0F;
  explosion_size=anim_explosion;
  if (explosion_size<0.0F){
    animation_phase=4;
    explosion_size=0.0F;
  }
}

void phaseExplosion4 (float animation_time) {
  anim_fummee += animation_time * 3.0F;
  fummee_size -= animation_time * 0.01F;
  fummee_idle ();
  tremblement+=1.0F;
  if (fummee_size<0.0F){
    animation_phase=0;
    fummee_size=0.0F;
  }
}

// animation_time est la vitesse d'animation
void explosion_idle (float animation_time) {
  switch(animation_phase){
    case 1:
      phaseExplosion1(animation_time);
      break;
    case 2:
      phaseExplosion2(animation_time);
      break;
    case 3:
      phaseExplosion3(animation_time);
      break;
    case 4:
      phaseExplosion4(animation_time);
      break;
  }
}



 
