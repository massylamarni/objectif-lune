#include "minimap.h"
#include "../render/camera.h"
#include "../render/models.h"
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <algorithm>
#include <deque>

namespace ui {
std::deque<Vec3> g_orbit_trail_positions;
bool g_orbit_main_view_enabled = false;

void apply_perspective(float fov_degrees, float aspect, float near_plane,
                       float far_plane) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(fov_degrees, aspect, near_plane, far_plane);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void apply_orthographic(float half_extent, float near_plane, float far_plane) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-half_extent, half_extent, -half_extent, half_extent, near_plane,
          far_plane);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void setup_viewport(const MinimapViewport &viewport) {
  glViewport(viewport.x, viewport.y, viewport.width, viewport.height);
  glEnable(GL_SCISSOR_TEST);
  glScissor(viewport.x, viewport.y, viewport.width, viewport.height);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glDisable(GL_SCISSOR_TEST);
}

void draw_world(const world::Ship &ship, const world::Planet &earth,
                const world::Planet &moon, const world::Planet &sun) {
  Vec3 sun_dir = sun.position;
  const float len = length(sun_dir);
  if (len > 0.0f) {
    sun_dir = sun_dir / len;
  }
  const float light_pos[4] = {sun_dir.x, sun_dir.y, sun_dir.z, 0.0f};
  glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

  render::draw_planet(earth);
  render::draw_planet(moon);
  render::draw_planet(sun);
  render::draw_ship(ship);
}

void draw_minimap_ship_marker(const world::Ship &ship, float marker_radius) {
  glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT | GL_ENABLE_BIT);
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_LIGHTING);

  glPushMatrix();
  glTranslatef(ship.position.x, ship.position.y, ship.position.z);
  glScalef(marker_radius, marker_radius, marker_radius);
  render::draw_mini_ship(ship);
  glPopMatrix();

  glPopAttrib();
}

void update_orbit_trail(const world::Ship &ship) {
  const float speed = length(ship.velocity);
  const int target_points =
      std::clamp(static_cast<int>(TRAIL_LENGTH + speed * TRAIL_SENSITIVITY), TRAIL_MIN_LEN, TRAIL_MAX_LEN);

  if (g_orbit_trail_positions.empty()) {
    g_orbit_trail_positions.push_back(ship.position);
  } else {
    const float min_spacing = std::max(0.15f, speed * 0.02f);
    if (length(ship.position - g_orbit_trail_positions.back()) >= min_spacing) {
      g_orbit_trail_positions.push_back(ship.position);
    }
  }

  while (static_cast<int>(g_orbit_trail_positions.size()) > target_points) {
    g_orbit_trail_positions.pop_front();
  }
}

void draw_orbit_trail() {
  if (g_orbit_trail_positions.size() < 2) {
    return;
  }

  glPushAttrib(GL_ENABLE_BIT | GL_LINE_BIT | GL_CURRENT_BIT | GL_LIGHTING_BIT);
  glDisable(GL_LIGHTING);
  glDisable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glLineWidth(TRAIL_WIDTH);

  glBegin(GL_LINE_STRIP);
  const int count = static_cast<int>(g_orbit_trail_positions.size());
  for (int i = 0; i < count; ++i) {
    const float t = static_cast<float>(i + 1) / static_cast<float>(count);
    const float alpha = 0.08f + 0.8f * t;
    glColor4f(0.25f, 0.85f, 1.0f, alpha);
    const Vec3 &p = g_orbit_trail_positions[i];
    glVertex3f(p.x, p.y, p.z);
  }
  glEnd();

  glPopAttrib();
}

const world::Planet &closest_planet(const world::Ship &ship,
                                    const world::Planet &earth,
                                    const world::Planet &moon,
                                    const world::Planet &sun) {
  const world::Planet *closest = &earth;
  float best_distance = world::distance_to_surface(earth, ship.position);

  const float moon_distance = world::distance_to_surface(moon, ship.position);
  if (moon_distance < best_distance) {
    best_distance = moon_distance;
    closest = &moon;
  }

  const float sun_distance = world::distance_to_surface(sun, ship.position);
  if (sun_distance < best_distance) {
    closest = &sun;
  }

  return *closest;
}

Vec3 safe_normalize(const Vec3 &v, const Vec3 &fallback) {
  const float l = length(v);
  if (l < 1e-4f) {
    return fallback;
  }
  return v / l;
}

render::Camera landing_assist_camera(const world::Ship &ship,
                                     const world::Planet &planet) {
  const Vec3 radial_up =
      safe_normalize(ship.position - planet.position, Vec3(0.0f, 1.0f, 0.0f));

  Vec3 tangent = cross(radial_up, Vec3(0.0f, 1.0f, 0.0f));
  if (length(tangent) < 1e-4f) {
    tangent = cross(radial_up, Vec3(1.0f, 0.0f, 0.0f));
  }
  tangent = safe_normalize(tangent, Vec3(0.0f, 0.0f, 1.0f));

  const float camera_distance = std::max(planet.radius * 1.1f, 120.0f);
  const Vec3 camera_position = ship.position + tangent * camera_distance;
  return render::create_camera(camera_position, ship.position, radial_up);
}

render::Camera
orbit_map_camera(const world::Ship &ship, const world::Planet &center_planet,
                 const world::Planet &earth, const world::Planet &moon,
                 const world::Planet &sun, float &half_extent_out) {
  float half_extent =
      std::max(center_planet.radius * 2.8f,
               length(ship.position - center_planet.position) * 1.4f);

  const world::Planet *planets[3] = {&earth, &moon, &sun};
  for (const world::Planet *planet : planets) {
    if (planet->id == center_planet.id) {
      continue;
    }
    const float center_to_planet =
        length(planet->position - center_planet.position);
    const float ship_to_planet =
        world::distance_to_surface(*planet, ship.position);
    if (ship_to_planet < center_planet.radius * 4.0f) {
      half_extent =
          std::max(half_extent, center_to_planet + planet->radius * 1.2f);
    }
  }

  half_extent = std::clamp(half_extent, 300.0f, 50000.0f);
  half_extent_out = half_extent;

  const float camera_height =
      std::max(half_extent * 4.0f, center_planet.radius * 6.0f);
  const Vec3 camera_position =
      center_planet.position + Vec3(0.0f, camera_height, 0.0f);
  return render::create_camera(camera_position, center_planet.position,
                               Vec3(0.0f, 0.0f, -1.0f));
}

void toggle_orbit_main_view(bool key_state) {
  static bool key_prev_state = false;
  if (key_state && !key_prev_state)
    g_orbit_main_view_enabled = !g_orbit_main_view_enabled;
  key_prev_state = key_state;
}

bool is_orbit_main_view_enabled() { return g_orbit_main_view_enabled; }

void draw_minimaps(const world::Ship &ship, const world::Planet &earth,
                   const world::Planet &moon, const world::Planet &sun,
                   const render::Camera &game_camera) {
  const int window_width = glutGet(GLUT_WINDOW_WIDTH);
  const int window_height = glutGet(GLUT_WINDOW_HEIGHT);

  const world::Planet &closest = closest_planet(ship, earth, moon, sun);
  const float closest_distance =
      world::distance_to_surface(closest, ship.position);

  float orbit_half_extent = 1000.0f;
  const render::Camera orbit_cam =
      orbit_map_camera(ship, closest, earth, moon, sun, orbit_half_extent);
  update_orbit_trail(ship);

  const MinimapViewport orbit_map = {
      MINIMAP_MARGINS, MINIMAP_MARGINS, 200, 200};

  const MinimapViewport landing_map = {
      MINIMAP_MARGINS*2 + orbit_map.width, MINIMAP_MARGINS, 100, 200};

  if (g_orbit_main_view_enabled) {
    const MinimapViewport full_screen = {0, 0, window_width, window_height};
    setup_viewport(full_screen);
    apply_orthographic(orbit_half_extent, 0.1f, 1000000.0f);
    render::camera_apply(orbit_cam);
    draw_world(ship, earth, moon, sun);
    draw_orbit_trail();
    draw_minimap_ship_marker(ship, orbit_half_extent * 0.03f);

    setup_viewport(orbit_map);
    const float preview_aspect = static_cast<float>(orbit_map.width) /
                                 static_cast<float>(orbit_map.height);
    apply_perspective(MAIN_FOV_DEG, preview_aspect, 0.1f, 1000000.0f);
    render::camera_apply(game_camera);
    draw_world(ship, earth, moon, sun);
  } else {
    setup_viewport(orbit_map);
    apply_orthographic(orbit_half_extent, 0.1f, 1000000.0f);
    render::camera_apply(orbit_cam);
    draw_world(ship, earth, moon, sun);
    draw_orbit_trail();
    draw_minimap_ship_marker(ship, orbit_half_extent * 0.03f);
  }

  if (closest_distance < closest.radius * LANDING_TRIGGER_MULTIPLIER) {
    setup_viewport(landing_map);

    const render::Camera landing_cam = landing_assist_camera(ship, closest);
    const float aspect = static_cast<float>(landing_map.width) /
                         static_cast<float>(landing_map.height);
    apply_perspective(MINIMAP_1_FOV_DEG, aspect, 0.1f, 1000000.0f);
    render::camera_apply(landing_cam);
    draw_world(ship, earth, moon, sun);
    draw_minimap_ship_marker(ship, std::max(closest.radius * 0.02f, 2.5f));
  }

  glViewport(0, 0, window_width, window_height);
  const float main_aspect =
      static_cast<float>(window_width) / static_cast<float>(window_height);
  apply_perspective(MAIN_FOV_DEG, main_aspect, 0.1f, 1000000.0f);
}
} // namespace ui
