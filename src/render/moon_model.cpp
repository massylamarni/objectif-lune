#include "moon_model.h"
#include "../math/noise.h"
#include <limits.h>

moon_scene current_scene = MOON_SCENE_ORBIT;
moon_transition_state transition = {false, false, 0.0f, 0};

moon_scene &get_moon_scene() { return current_scene; };

void set_moon_scene(moon_scene ms) { current_scene= ms; };

static float heightmap[GRID_STEPS + 1][GRID_STEPS + 1];
static Vec3 normalmap[GRID_STEPS + 1][GRID_STEPS + 1];

static int last_grid_x = INT_MIN;
static int last_grid_z = INT_MIN;

void update_terrain_cache(float origin_x, float origin_z, float step,
                          float half) {
  for (int i = 0; i <= GRID_STEPS; ++i) {
    for (int j = 0; j <= GRID_STEPS; ++j) {

      float x = i * step - half;
      float z = j * step - half;

      float wx = x + origin_x;
      float wz = z + origin_z;

      float h = get_lunar_height(wx, wz);
      heightmap[i][j] = h;

      float hL = get_lunar_height(wx - step, wz);
      float hR = get_lunar_height(wx + step, wz);
      float hD = get_lunar_height(wx, wz - step);
      float hU = get_lunar_height(wx, wz + step);

      float nx = hL - hR;
      float ny = 2.0f * step;
      float nz = hD - hU;

      float len = std::sqrt(nx * nx + ny * ny + nz * nz);
      if (len == 0.0f)
        len = 1.0f;

      normalmap[i][j] = {nx / len, ny / len, nz / len};
    }
  }
}

void draw_moon_container(const world::Planet &planet, Vec3 *ship_position) {
  const uint *texture_id_buf = render::get_texture_id_buf();
  if (ship_position != nullptr) {
    const float moon_distance =
        current_scene == MOON_SCENE_ORBIT
            ? world::distance_to_surface(planet, *ship_position)
            : ship_position->y;
    update_moon_transition(moon_distance, ship_position);
  }

  material_white();
  if (current_scene == MOON_SCENE_ORBIT) {
    glBindTexture(GL_TEXTURE_2D, texture_id_buf[render::MOON_TEXTURE]);
    glRotatef (90.0f, 1.0f, 0.0f, 0.0f);
    draw_planet_sphere(planet.radius);
  } else if (current_scene == MOON_SCENE_SURFACE) {
    glBindTexture(GL_TEXTURE_2D, texture_id_buf[render::MOON_SURFACE_TEXTURE]);
    draw_moon_surface(ship_position);
  }
}

void draw_planet_sphere(float radius) {
  GLUquadric *quad = gluNewQuadric();
  gluQuadricTexture(quad, GL_TRUE);
  gluQuadricNormals(quad, GLU_SMOOTH);
  gluSphere(quad, radius, 32, 32);
  gluDeleteQuadric(quad);
}

float get_lunar_height(float x, float z) { return fbm(x, z) * 50.0f; }

void compute_normal(float x, float z, float step, float &nx, float &ny,
                    float &nz) {
  float hL = get_lunar_height(x - step, z);
  float hR = get_lunar_height(x + step, z);
  float hD = get_lunar_height(x, z - step);
  float hU = get_lunar_height(x, z + step);

  nx = hL - hR;
  ny = 2.0f * step;
  nz = hD - hU;

  float len = std::sqrt(nx * nx + ny * ny + nz * nz);
  if (len == 0.0f)
    len = 1.0f;

  nx /= len;
  ny /= len;
  nz /= len;
}

void draw_moon_surface(Vec3 *ship_position) {
  if (!ship_position)
    return;

  const float step = PATCH_SIZE / GRID_STEPS;
  const float half = PATCH_SIZE / 2.0f;
  const float TEXTURE_SCALE = 0.01f;

  int grid_x = (int)std::floor(ship_position->x / step);
  int grid_z = (int)std::floor(ship_position->z / step);

  float origin_x = grid_x * step;
  float origin_z = grid_z * step;

  // Only recompute when entering a new cell
  if (grid_x != last_grid_x || grid_z != last_grid_z) {
    update_terrain_cache(origin_x, origin_z, step, half);
    last_grid_x = grid_x;
    last_grid_z = grid_z;
  }

  glPushMatrix();
  glTranslatef(origin_x, 0.0f, origin_z);

  for (int j = 0; j < GRID_STEPS; ++j) {

    glBegin(GL_TRIANGLE_STRIP);

    for (int i = 0; i <= GRID_STEPS; ++i) {

      float x = i * step - half;
      float z0 = j * step - half;
      float z1 = (j + 1) * step - half;

      float wx = x + origin_x;
      float wz0 = z0 + origin_z;
      float wz1 = z1 + origin_z;

      Vec3 n0 = normalmap[i][j];
      glNormal3f(n0.x, n0.y, n0.z);
      glTexCoord2f(wx * TEXTURE_SCALE, wz0 * TEXTURE_SCALE);
      glVertex3f(x, heightmap[i][j], z0);

      Vec3 n1 = normalmap[i][j + 1];
      glNormal3f(n1.x, n1.y, n1.z);
      glTexCoord2f(wx * TEXTURE_SCALE, wz1 * TEXTURE_SCALE);
      glVertex3f(x, heightmap[i][j + 1], z1);
    }

    glEnd();
  }

  glPopMatrix();
}

void teleport_player_to_surface(Vec3 *ship_position) {
  float x = 0.0f;
  float z = 0.0f;
  float y = get_lunar_height(x, z) + 500.0f;

  *ship_position = Vec3{x, y, z};
}

void update_moon_transition(float moon_distance, Vec3 *ship_position) {
  const int now = glutGet(GLUT_ELAPSED_TIME);
  float dt = (now - transition.last_time) / 1000.0f;
  transition.last_time = now;

  if (dt > 0.1f)
    dt = 0.1f;
  if (dt < 0.0f)
    dt = 0.0f;

  if (!transition.active && current_scene == MOON_SCENE_ORBIT &&
      moon_distance <= ENTER_SURFACE_DISTANCE) {

    transition.active = true;
    transition.fading_out = true;
  }

  if (!transition.active && current_scene == MOON_SCENE_SURFACE &&
      moon_distance >= EXIT_SURFACE_DISTANCE) {

    transition.active = true;
    transition.fading_out = true;
  }

  if (!transition.active)
    return;

  if (transition.fading_out) {
    transition.alpha += TERRAIN_TRANSITION_SPEED * dt;

    if (transition.alpha >= 1.0f) {
      transition.alpha = 1.0f;

      if (current_scene == MOON_SCENE_ORBIT) {
        current_scene = MOON_SCENE_SURFACE;
        teleport_player_to_surface(ship_position);
      } else {
        current_scene = MOON_SCENE_ORBIT;
        // TODO Teleport player back
      }

      transition.fading_out = false;
    }
  } else {
    transition.alpha -= TERRAIN_TRANSITION_SPEED * dt;

    if (transition.alpha <= 0.0f) {
      transition.alpha = 0.0f;
      transition.active = false;
    }
  }
}

void draw_moon_transition_overlay() {
  if (transition.alpha <= 0.0f) {
    return;
  }

  const int width = glutGet(GLUT_WINDOW_WIDTH);
  const int height = glutGet(GLUT_WINDOW_HEIGHT);

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0, width, 0, height);

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT | GL_DEPTH_BUFFER_BIT);
  glDisable(GL_LIGHTING);
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glColor4f(0.0f, 0.0f, 0.0f, transition.alpha);
  glBegin(GL_QUADS);
  glVertex2f(0.0f, 0.0f);
  glVertex2f(static_cast<float>(width), 0.0f);
  glVertex2f(static_cast<float>(width), static_cast<float>(height));
  glVertex2f(0.0f, static_cast<float>(height));
  glEnd();

  glPopAttrib();
  glPopMatrix();

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
}
