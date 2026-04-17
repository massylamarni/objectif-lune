#ifndef POLYFACE_OBJECT
#define POLYFACE_OBJECT

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

float textureRandom ();

void PolyFaceCylindre (float hauteur, float rayon, int ns, int tex_part_index, bool randomTexture);

void PolyFaceConeCut (float hauteur, float rayon_A, float rayon_B, int ns, int tex_part_index);

void PolyFacePrism (int face, int total_face, float height, float length_A, float length_B, int nbPolygon, bool closed, int tex_part_index, bool randomTexture);

void PolyFaceSurface (float size_x, float size_y, int nbPolygon_x, int nbPolygon_y, int tex_part_index, bool randomTexture);

void PolyFaceCube (float size, int nbPolygon, int tex_part_index);

#endif
