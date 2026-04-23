#include "moon_model.h"

moon_scene current_scene = MOON_SCENE_ORBIT;
moon_transition_state transition = {false, false, 0.0f, 0};

void draw_moon_container(const world::Planet &planet, Vec3 *ship_position) {
  const uint *texture_id_buf = render::get_texture_id_buf();
  if (ship_position != nullptr) {
    const float moon_distance =
        current_scene == MOON_SCENE_ORBIT
            ? world::distance_to_surface(planet, *ship_position)
            : ship_position->y;
    update_moon_transition(moon_distance, ship_position);
  }
  if (current_scene == MOON_SCENE_ORBIT) {
    draw_moon(planet, ship_position);
  } else if (current_scene == MOON_SCENE_SURFACE) {
    draw_moon_surface(ship_position);
  }
}

void draw_moon(const world::Planet &planet, const Vec3 *ship_position) {
  const uint *texture_id_buf = render::get_texture_id_buf();

  material_white();
  glBindTexture(GL_TEXTURE_2D, texture_id_buf[render::MOON_TEXTURE]);

  if (current_scene == MOON_SCENE_ORBIT) {
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

void draw_moon_surface(Vec3 *ship_position) {
  if (!ship_position)
    return;
  const float PATCH_SIZE = 2000.0f;
  const int GRID_STEPS = 128;
  const float step = PATCH_SIZE / GRID_STEPS;
  const float half = PATCH_SIZE / 2.0f;

  glPushMatrix();

  glTranslatef(ship_position->x, 0.0f, ship_position->z);

  glBegin(GL_QUADS);
  for (int i = 0; i < GRID_STEPS; ++i) {
    for (int j = 0; j < GRID_STEPS; ++j) {
      float x0 = i * step - half;
      float z0 = j * step - half;
      float x1 = x0 + step;
      float z1 = z0 + step;

      float world_x0 = x0 + ship_position->x;
      float world_z0 = z0 + ship_position->z;

      float world_x1 = x1 + ship_position->x;
      float world_z1 = z1 + ship_position->z;

      float y00 = get_lunar_height(world_x0, world_z0);
      float y10 = get_lunar_height(world_x1, world_z0);
      float y01 = get_lunar_height(world_x0, world_z1);
      float y11 = get_lunar_height(world_x1, world_z1);

      // Normals
      float sx = step;
      float sz = step;
      float nx = (y00 - y10);
      float nz = (y00 - y01);
      float ny = 2.0f;
      float length = std::sqrt(nx * nx + ny * ny + nz * nz);
      if (length == 0.0f)
        length = 1.0f;
      nx /= length;
      ny /= length;
      nz /= length;
      glNormal3f(nx, ny, nz);

      glVertex3f(x0, y00, z0);
      glVertex3f(x1, y10, z0);
      glVertex3f(x1, y11, z1);
      glVertex3f(x0, y01, z1);
    }
  }
  glEnd();

  glPopMatrix();
}

void teleport_player_to_surface(Vec3 *ship_position) {
  float x = 0.0f;
  float z = 0.0f;
  float y = get_lunar_height(x, z) + 5.0f;

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
