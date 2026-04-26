#include "../../assets/models/explosion.h"
#include "../../assets/models/lem.h"
#include "../math/vec3.h"
#include "../world/planet.h"
#include "textures.h"
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define ENTER_SURFACE_DISTANCE 250.0f // TODO make it relative to planet size
#define EXIT_SURFACE_DISTANCE 350.0f
#define TERRAIN_TRANSITION_SPEED 1.8f
#define PATCH_SIZE 2000.0f
#define GRID_STEPS 128

enum moon_scene { MOON_SCENE_ORBIT, MOON_SCENE_SURFACE };

struct moon_transition_state {
  bool active;
  bool fading_out;
  float alpha;
  int last_time;
};

void compute_normal(float x, float z, float step, float &nx, float &ny,
                    float &nz);
float get_lunar_height(float wx, float wz);
void draw_moon_container(const world::Planet &planet, Vec3 *ship_position);
void draw_planet_sphere(float radius);
void draw_moon_surface(Vec3 *ship_position);
void update_moon_transition(float moon_distance, Vec3 *ship_position);
void draw_moon_transition_overlay();
moon_scene &get_moon_scene();
