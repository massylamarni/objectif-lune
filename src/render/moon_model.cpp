#include "moon_model.h"

moon_transition_state moon_ts = {false,      MOON_SPHERE, MOON_SPHERE,
                                 PHASE_NONE, 0.0f,        0};

void draw_moon(const world::Planet &planet, const Vec3 *ship_position) {
  const uint *texture_id_buf = render::get_texture_id_buf();
  if (ship_position != nullptr) {
    const float moon_distance =
        world::distance_to_surface(planet, *ship_position);
    update_moon_transition(moon_distance);
  }

  material_white();
  glBindTexture(GL_TEXTURE_2D, texture_id_buf[render::MOON_TEXTURE]);
  if (moon_ts.current_mode == MOON_SURFACE && ship_position != nullptr) {
    draw_moon_surface_patch(planet, *ship_position);
  } else {
    draw_planet_sphere(planet.radius);
  }
}

void draw_planet_sphere(float radius) {
  GLUquadric *quad = gluNewQuadric();
  gluQuadricTexture(quad, GL_TRUE);
  gluQuadricNormals(quad, GLU_SMOOTH);
  gluSphere(quad, radius, 32, 32);
  gluDeleteQuadric(quad);
}

float get_lunar_height(float x, float z) {
  float height = 0.0f;
  height += std::sin(x * 0.005f) * std::cos(z * 0.005f) * 30.0f;
  height += std::sin(x * 0.05f + 1.0f) * std::cos(z * 0.04f - 0.5f) * 5.0f;
  height += std::sin(x * 0.2f) * std::sin(z * 0.2f) * 1.5f;
  return height;
}

void draw_moon_surface_patch(const world::Planet &planet,
                             const Vec3 &ship_position) {
  float dist = std::sqrt(ship_position.x * ship_position.x +
                         ship_position.y * ship_position.y +
                         ship_position.z * ship_position.z);

  if (dist < 0.0001f)
    dist = 1.0f;

  float nx = ship_position.x / dist;
  float ny = ship_position.y / dist;
  float nz = ship_position.z / dist;

  float surface_x = nx * planet.radius;
  float surface_y = ny * planet.radius;
  float surface_z = nz * planet.radius;

  float axis_x = nz;
  float axis_y = 0.0f;
  float axis_z = -nx;

  float dot = ny;
  if (dot > 1.0f)
    dot = 1.0f;
  if (dot < -1.0f)
    dot = -1.0f;
  float angle_deg = std::acos(dot) * 180.0f / 3.14159265359f;

  glPushMatrix();

  glTranslatef(surface_x, surface_y, surface_z);

  if (dot < 0.999f && dot > -0.999f) {
    glRotatef(angle_deg, axis_x, axis_y, axis_z);
  } else if (dot <= -0.999f) {
    glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
  }

  const float PATCH_SIZE = 2000.0f;
  const int GRID_STEPS = 64;
  const float step_size = PATCH_SIZE / GRID_STEPS;
  const float uv_scale = 15.0f;
  const float half_size = PATCH_SIZE / 2.0f;

  glBegin(GL_QUADS);
  for (int i = 0; i < GRID_STEPS; ++i) {
    for (int j = 0; j < GRID_STEPS; ++j) {
      float local_x0 = (i * step_size) - half_size;
      float local_z0 = (j * step_size) - half_size;
      float local_x1 = local_x0 + step_size;
      float local_z1 = local_z0 + step_size;

      float global_x0 = local_x0 + surface_x;
      float global_z0 = local_z0 + surface_z;
      float global_x1 = local_x1 + surface_x;
      float global_z1 = local_z1 + surface_z;

      float y00 = get_lunar_height(global_x0, global_z0);
      float y10 = get_lunar_height(global_x1, global_z0);
      float y01 = get_lunar_height(global_x0, global_z1);
      float y11 = get_lunar_height(global_x1, global_z1);

      float nx_norm = -step_size * (y10 - y00);
      float ny_norm = step_size * step_size;
      float nz_norm = -step_size * (y01 - y00);
      float length =
          std::sqrt(nx_norm * nx_norm + ny_norm * ny_norm + nz_norm * nz_norm);
      glNormal3f(nx_norm / length, ny_norm / length, nz_norm / length);

      float u0 = (global_x0 / PATCH_SIZE) * uv_scale;
      float v0 = (global_z0 / PATCH_SIZE) * uv_scale;
      float u1 = (global_x1 / PATCH_SIZE) * uv_scale;
      float v1 = (global_z1 / PATCH_SIZE) * uv_scale;

      glTexCoord2f(u0, v0);
      glVertex3f(local_x0, y00, local_z0);
      glTexCoord2f(u1, v0);
      glVertex3f(local_x1, y10, local_z0);
      glTexCoord2f(u1, v1);
      glVertex3f(local_x1, y11, local_z1);
      glTexCoord2f(u0, v1);
      glVertex3f(local_x0, y01, local_z1);
    }
  }
  glEnd();

  glPopMatrix();
}

void update_moon_transition(float moon_distance) {
  const int now_ms = glutGet(GLUT_ELAPSED_TIME);
  if (!moon_ts.initialized) {
    moon_ts.current_mode =
        (moon_distance <= TERRAIN_SWAP_DISTANCE) ? MOON_SURFACE : MOON_SPHERE;
    moon_ts.pending_mode = moon_ts.current_mode;
    moon_ts.phase = PHASE_NONE;
    moon_ts.fade_alpha = 0.0f;
    moon_ts.last_update_ms = now_ms;
    moon_ts.initialized = true;
    return;
  }

  const moon_render_mode wanted_mode =
      (moon_distance <= TERRAIN_SWAP_DISTANCE) ? MOON_SURFACE : MOON_SPHERE;
  if (moon_ts.phase == PHASE_NONE && wanted_mode != moon_ts.current_mode) {
    moon_ts.pending_mode = wanted_mode;
    moon_ts.phase = PHASE_FADE_OUT;
  }

  float dt = (now_ms - moon_ts.last_update_ms) / 1000.0f;
  if (dt < 0.0f)
    dt = 0.0f;
  if (dt > 0.1f)
    dt = 0.1f;
  moon_ts.last_update_ms = now_ms;

  if (moon_ts.phase == PHASE_FADE_OUT) {
    moon_ts.fade_alpha += TERRAIN_TRANSITION_SPEED * dt;
    if (moon_ts.fade_alpha >= 1.0f) {
      moon_ts.fade_alpha = 1.0f;
      moon_ts.current_mode = moon_ts.pending_mode;
      moon_ts.phase = PHASE_FADE_IN;
    }
  } else if (moon_ts.phase == PHASE_FADE_IN) {
    moon_ts.fade_alpha -= TERRAIN_TRANSITION_SPEED * dt;
    if (moon_ts.fade_alpha <= 0.0f) {
      moon_ts.fade_alpha = 0.0f;
      moon_ts.phase = PHASE_NONE;
    }
  }
}

void draw_moon_transition_overlay() {
  if (!moon_ts.initialized || moon_ts.fade_alpha <= 0.0f) {
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

  glColor4f(0.0f, 0.0f, 0.0f, moon_ts.fade_alpha);
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
