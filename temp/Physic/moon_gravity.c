 /* Configuration par défault de variable OpenGL */ 
 /*                                              */ 
 /* Projet Objectif Lune                         */ 



#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "moon_gravity.h"

double distance_barycentered;
struct vec3d position;
struct vec3d speed;

struct vec3d tail [TAIL_SIZE];

double vec3d_length (struct vec3d vec) {
  return sqrt ((vec.v_x * vec.v_x) + (vec.v_y * vec.v_y) + (vec.v_z * vec.v_z));
}

void init_orbit () {
  position.v_x = 50.0;
  position.v_y = 0.0;
  position.v_z = 0.0;
  
  speed.v_x = 0.0;
  speed.v_y = 0.3;
  speed.v_z = 0.0;
  
  for (int i = 0 ; i < TAIL_SIZE ; i++) {
    tail [i].v_x = 50.0;
    tail [i].v_y = 0.0;
    tail [i].v_z = 0.0;
  }
}

void step () {
  for (int i = TAIL_SIZE - 1 ; i > 0 ; i--) { // Décalage
    tail [i].v_x = tail [i - 1].v_x;
    tail [i].v_y = tail [i - 1].v_y;
    tail [i].v_z = tail [i - 1].v_z;
  }
  printf("<<<%.2f>>>", tail  [8].v_x);
  
  position.v_x += speed.v_x;
  position.v_y += speed.v_y;
  position.v_z += speed.v_z;
  
  tail [0].v_x = position.v_x;
  tail [0].v_y = position.v_y;
  tail [0].v_z = position.v_z;
  
  distance_barycentered = vec3d_length (position);
  
  speed.v_x += -0.1 * position.v_x / (distance_barycentered * distance_barycentered);
  speed.v_y += -0.1 * position.v_y / (distance_barycentered * distance_barycentered);
  speed.v_z += -0.1 * position.v_z / (distance_barycentered * distance_barycentered);
  
  if (fabs (position.v_x) < 1) {
    speed.v_x += position.v_x / (distance_barycentered * distance_barycentered);
  }
  if (fabs (position.v_y) < 1) {
    speed.v_y += position.v_y / (distance_barycentered * distance_barycentered);
  }
  if (fabs (position.v_z) < 1) {
    speed.v_z += position.v_z / (distance_barycentered * distance_barycentered);
  }
  
  printf ("GAIN {%.2f, %.2f, %.2f}  \t%.2f\n", -1 * position.v_x / (distance_barycentered * distance_barycentered), -1 * position.v_y / (distance_barycentered * distance_barycentered), -1 * position.v_z / (distance_barycentered * distance_barycentered), distance_barycentered);
  
  printf ("Speed {%.2f}  \t", speed.v_x);
  
}

/*int main (int argc, char ** argv) {
  int iteration_counter = 5;
  if (argc > 1) {
    iteration_counter = atoi (argv [1]);
  }
  
  init_orbit ();
  
  printf ("POSITON {%.2f, %.2f, %.2f}   \t", position.v_x, position.v_y, position.v_z);
  printf ("SPEED {%.2f, %.2f, %.2f}\n", speed.v_x, speed.v_y, speed.v_z);
  
  while (iteration_counter != 0) {
    step ();
    
    printf ("POSITON {%.2f, %.2f, %.2f}  \t", position.v_x, position.v_y, position.v_z);
    printf ("SPEED {%.2f, %.2f, %.2f}  \t", speed.v_x, speed.v_y, speed.v_z);
    
    iteration_counter--;
  }
  printf("\n");
  
  return 0;
}*/
