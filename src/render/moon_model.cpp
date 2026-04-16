#include "moon_model.h"

namespace models {
struct PrecomputedVertex {
  Vec3 base_dir;
  float raw_h;
  Vec3 grad_vec;
  float u_tex, v_tex;
};

static GLuint s_terrain_list = 0;
static float s_last_t = -1.0f;
static GLUquadric *s_quadric = nullptr;
static std::vector<PrecomputedVertex> s_precomp_grid;
static bool s_initialized = false;

void build_moon_tangent_frame(const Vec3 &surface_normal, Vec3 *e1, Vec3 *e2) {
  const Vec3 ref = (std::fabs(surface_normal.y) < 0.9f)
                       ? Vec3(0.0f, 1.0f, 0.0f)
                       : Vec3(1.0f, 0.0f, 0.0f);
  *e1 = cross(ref, surface_normal);
  const float len = length(*e1);
  *e1 = (len < 1e-5f) ? Vec3(1.0f, 0.0f, 0.0f) : (*e1 / len);
  *e2 = normalize(cross(surface_normal, *e1));
}

void initialize_grid(const world::Planet &moon) {
  const int SIZE = MOON_TERRAIN_SIZE;
  const float SCALE = MOON_TERRAIN_SCALE;
  const float half = (float)SIZE * 0.5f;
  const float inv_radius = 1.0f / moon.radius;

  s_precomp_grid.resize(SIZE * SIZE);

  for (int z = 0; z < SIZE; z++) {
    for (int x = 0; x < SIZE; x++) {
      float xc = ((float)x - half) * SCALE;
      float zc = ((float)z - half) * SCALE;

      PrecomputedVertex &pv = s_precomp_grid[z * SIZE + x];
      pv.base_dir = normalize(Vec3(xc * inv_radius, 1.0f, zc * inv_radius));

      float h = 0.0f;
      float dx = 0.0f;
      float dz = 0.0f;

      // Base rolling hills (Low frequency, high amplitude)
      float f1 = 0.02f;
      float a1 = 1.0f;
      h += a1 * std::sin(xc * f1) * std::cos(zc * f1);
      dx += a1 * f1 * std::cos(xc * f1) * std::cos(zc * f1);
      dz -= a1 * f1 * std::sin(xc * f1) * std::sin(zc * f1);

      // Mid-level irregularities (Offset phase to break the grid)
      float fx2 = 0.057f, fz2 = 0.043f;
      float a2 = 0.4f;
      h += a2 * std::sin(xc * fx2 + 1.2f) * std::cos(zc * fz2 + 0.8f);
      dx += a2 * fx2 * std::cos(xc * fx2 + 1.2f) * std::cos(zc * fz2 + 0.8f);
      dz -= a2 * fz2 * std::sin(xc * fx2 + 1.2f) * std::sin(zc * fz2 + 0.8f);

      // High-frequency spikes/details
      float fx3 = 0.131f, fz3 = 0.173f;
      float a3 = 0.15f;
      h += a3 * std::sin(xc * fx3 - 0.5f) * std::cos(zc * fz3 + 2.1f);
      dx += a3 * fx3 * std::cos(xc * fx3 - 0.5f) * std::cos(zc * fz3 + 2.1f);
      dz -= a3 * fz3 * std::sin(xc * fx3 - 0.5f) * std::sin(zc * fz3 + 2.1f);

      pv.raw_h = h * MOON_HEIGHT_BIAS;

      pv.grad_vec = Vec3(-dx * MOON_HEIGHT_BIAS, 0.0f, -dz * MOON_HEIGHT_BIAS);

      pv.u_tex = xc * 0.01f;
      pv.v_tex = zc * 0.01f;
    }
  }
  s_initialized = true;
}

void draw_moon_sphere(const world::Planet &planet) {
  if (!s_quadric) {
    s_quadric = gluNewQuadric();
    gluQuadricTexture(s_quadric, GL_TRUE);
    gluQuadricNormals(s_quadric, GLU_SMOOTH);
  }

  glPushMatrix();
  glTranslatef(planet.position.x, planet.position.y, planet.position.z);
  material_white();
  gluSphere(s_quadric, planet.radius, 32, 32);
  glPopMatrix();
}

void draw_moon_terrain(const world::Planet &moon, const Vec3 &ship_position,
                       float t) {
  if (!s_initialized)
    initialize_grid(moon);

  bool needs_rebuild = (s_terrain_list == 0 || std::abs(t - s_last_t) > 0.001f);

  if (needs_rebuild) {
    if (s_terrain_list == 0)
      s_terrain_list = glGenLists(1);
    s_last_t = t;

    const float raw_u = 1.0f - t;
    const float u_w = raw_u * raw_u * (3.0f - 2.0f * raw_u);
    const int SIZE = MOON_TERRAIN_SIZE;

    glNewList(s_terrain_list, GL_COMPILE);
    material_white();

    for (int z = 0; z < SIZE - 1; z++) {
      glBegin(GL_TRIANGLE_STRIP);
      for (int x = 0; x < SIZE; x++) {
        for (int row_off = 0; row_off < 2; row_off++) {
          const PrecomputedVertex &pv =
              s_precomp_grid[(z + row_off) * SIZE + x];

          float h = MOON_HEIGHT_BIAS + pv.raw_h * u_w;
          Vec3 pos = pv.base_dir * (moon.radius + h);

          Vec3 normal = normalize(pv.base_dir + (pv.grad_vec * u_w));

          glNormal3fv(&normal.x);
          glTexCoord2f(pv.u_tex, pv.v_tex);
          glVertex3fv(&pos.x);
        }
      }
      glEnd();
    }
    glEndList();
  }

  Vec3 to_ship = ship_position - moon.position;
  Vec3 normal = normalize(to_ship);
  Vec3 e1, e2;
  build_moon_tangent_frame(normal, &e1, &e2);

  float mat[16] = {e1.x,
                   e1.y,
                   e1.z,
                   0,
                   normal.x,
                   normal.y,
                   normal.z,
                   0,
                   e2.x,
                   e2.y,
                   e2.z,
                   0,
                   moon.position.x,
                   moon.position.y,
                   moon.position.z,
                   1};

  glPushMatrix();
  glMultMatrixf(mat);
  glCallList(s_terrain_list);
  glPopMatrix();
}

float get_moon_height_at_pos(const world::Planet &planet,
                             const Vec3 &ship_position, const Vec3 &target_pos,
                             float t) {
  Vec3 to_ship = normalize(ship_position - planet.position);
  Vec3 e1, e2;

  Vec3 ref = (std::fabs(to_ship.y) < 0.9f) ? Vec3(0.0f, 1.0f, 0.0f)
                                           : Vec3(1.0f, 0.0f, 0.0f);
  e1 = normalize(cross(ref, to_ship));
  e2 = normalize(cross(to_ship, e1));

  Vec3 rel_pos = target_pos - planet.position;
  float y_local = dot(rel_pos, to_ship);
  float x_local = dot(rel_pos, e1);
  float z_local = dot(rel_pos, e2);

  if (y_local <= 0.0f)
    return 0.0f;

  float xc = (x_local / y_local) * planet.radius;
  float zc = (z_local / y_local) * planet.radius;

  float h = 0.0f;
  h += 1.00f * std::sin(xc * 0.020f) * std::cos(zc * 0.020f);
  h += 0.40f * std::sin(xc * 0.057f + 1.2f) * std::cos(zc * 0.043f + 0.8f);
  h += 0.15f * std::sin(xc * 0.131f - 0.5f) * std::cos(zc * 0.173f + 2.1f);

  float raw_u = 1.0f - t;
  float u_w = raw_u * raw_u * (3.0f - 2.0f * raw_u);

  return (MOON_HEIGHT_BIAS + (h * MOON_HEIGHT_BIAS)) * u_w;
}

bool check_planet_collision(const physics::RigidBody &body,
                            const world::Planet &planet, const Vec3 &ship_pos,
                            float t) {
  float terrain_h = get_moon_height_at_pos(planet, ship_pos, body.position, t);

  Vec3 diff = body.position - planet.position;
  float dist = length(diff);

  return dist <= (planet.radius + terrain_h + body.radius);
}

void resolve_planet_collision(physics::RigidBody &body,
                              const world::Planet &planet, const Vec3 &ship_pos,
                              float t) {
  float terrain_h = get_moon_height_at_pos(planet, ship_pos, body.position, t);

  Vec3 normal = normalize(body.position - planet.position);
  body.position =
      planet.position + normal * (planet.radius + terrain_h + body.radius);

  float velocity_normal = dot(body.velocity, normal);
  if (velocity_normal < 0.0f) {
    body.velocity -= normal * velocity_normal;
  }
}

void update_ship_collision_state(world::Ship &ship, const world::Planet &planet,
                                 float t) {
  if (ship.state == world::SHIP_LANDED || ship.state == world::SHIP_DESTORYED) {
    return;
  }

  physics::RigidBody body;
  body.position = ship.position;
  body.radius = ship.radius;

  if (!check_planet_collision(body, planet, ship.position, t)) {
    ship.state = world::ship_state::SHIP_ROAMING;
    return;
  }

  resolve_planet_collision(body, planet, ship.position, t);
  ship.position = body.position;

  Vec3 to_planet = normalize(planet.position - ship.position);
  Vec3 ship_down = physics::ship_down_direction(ship);
  float landing_alignment = dot(ship_down, to_planet);
  float speed = length(ship.velocity);

  if (landing_alignment >= LANDING_ALIGNMENT_THRESHOLD) {
    ship.state = world::ship_state::SHIP_LANDED;
    ship.velocity = Vec3(0, 0, 0);
    return;
  }

  if (speed > CRASH_SPEED_THRESHOLD) {
    ship.state = world::ship_state::SHIP_DESTORYED;
    return;
  }

  ship.state = world::ship_state::SHIP_ROAMING;
}
}