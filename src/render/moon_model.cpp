#include "moon_model.h"
#include <vector>

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

      float xs = xc * 0.05f, zs = zc * 0.05f;
      float sx = std::sin(xs), cx = std::cos(xs);
      float sz = std::sin(zs), cz = std::cos(zs);

      PrecomputedVertex &pv = s_precomp_grid[z * SIZE + x];

      pv.base_dir = normalize(Vec3(xc * inv_radius, 1.0f, zc * inv_radius));

      pv.raw_h = sx * cz * MOON_HEIGHT_BIAS;

      float dx = 0.05f * cx * cz * MOON_HEIGHT_BIAS;
      float dz = -0.05f * sx * sz * MOON_HEIGHT_BIAS;

      pv.grad_vec = Vec3(-dx, 0.0f, -dz);
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