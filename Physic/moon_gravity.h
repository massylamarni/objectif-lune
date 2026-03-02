 /* Configuration par défault de variable OpenGL */ 
 /*                                              */ 
 /* Projet Objectif Lune                         */ 

#define TAIL_SIZE 100

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

struct vec3d {
  double v_x;
  double v_y;
  double v_z;
};

extern double distance_barycentered;
extern struct vec3d position;
extern struct vec3d speed;

extern struct vec3d tail [TAIL_SIZE];

double vec3d_length (struct vec3d vec);

void init_orbit ();

void step ();
