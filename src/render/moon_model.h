#include "../../assets/models/explosion.h"
#include "../../assets/models/lem.h"
#include "../math/vec3.h"
#include "../world/planet.h"
#include "textures.h"
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define TERRAIN_SWAP_DISTANCE 250.0f
#define TERRAIN_TRANSITION_SPEED 1.8f

enum moon_render_mode { MOON_SPHERE, MOON_SURFACE };
enum fade_transition_phase { PHASE_NONE, PHASE_FADE_OUT, PHASE_FADE_IN };

struct moon_transition_state {
  bool initialized;
  moon_render_mode current_mode;
  moon_render_mode pending_mode;
  fade_transition_phase phase;
  float fade_alpha;
  int last_update_ms;
};

void draw_moon(const world::Planet &planet, const Vec3 *ship_position);
void draw_planet_sphere(float radius);
void draw_moon_surface_patch(const world::Planet &planet,
                             const Vec3 &ship_position);
void update_moon_transition(float moon_distance);
void draw_moon_transition_overlay();