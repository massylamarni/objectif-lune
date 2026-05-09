#include "minimap.h"
#include "../render/camera.h"
#include "../render/models.h"
#include "../render/renderer.h"
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <algorithm>
#include <deque>

namespace ui {
std::deque<Vec3> g_orbit_trail_positions;
bool g_orbit_main_view_enabled = false;
bool g_landing_main_view_enabled = false;

void setup_viewport(const MinimapViewport &viewport) {
  glViewport(viewport.x, viewport.y, viewport.width, viewport.height);
  glEnable(GL_SCISSOR_TEST);
  glScissor(viewport.x, viewport.y, viewport.width, viewport.height);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glDisable(GL_SCISSOR_TEST);
}

void draw_world(const world::Ship &ship, const world::Planet &earth,
                const world::Planet &moon, const world::Planet &sun) {
  render::draw_mini_planet(earth, nullptr);
  render::draw_mini_planet(moon, nullptr);
  render::draw_mini_planet(sun, nullptr);
  render::draw_mini_ship(ship);
  render::draw_skybox(10000.0F, &(ship.position));
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

void draw_landing_world(const world::Ship &ship, const world::Planet &earth,
                        const world::Planet &moon, const world::Planet &sun) {
  render::draw_planet(moon, &const_cast<Vec3 &>(ship.position));
  render::draw_mini_ship(ship);
  render::draw_skybox(10000.0F, &(ship.position));
}

void update_orbit_trail(const world::Ship &ship) {
  const float speed = length(ship.velocity);
  const int target_points =
      std::clamp(static_cast<int>(TRAIL_LENGTH + speed * TRAIL_SENSITIVITY),
                 TRAIL_MIN_LEN, TRAIL_MAX_LEN);

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

void reset_orbit_trail() {
  g_orbit_trail_positions.clear();
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
  const Vec3 up(0.0f, 1.0f, 0.0f);

  float origin_x, origin_z;
  get_cached_origin(origin_x, origin_z);

  const float ship_terrain_height = get_interpolated_height(
      ship.position.x, ship.position.z, origin_x, origin_z);

  const float altitude = std::max(ship.position.y - ship_terrain_height, 0.0f);

  const float MIN_DISTANCE = 150.0f;
  const float MAX_DISTANCE = 500.0f;

  const float camera_distance =
      std::clamp(altitude, MIN_DISTANCE, MAX_DISTANCE);

  const float midpoint_y = ship_terrain_height + altitude * 0.65f;

  Vec3 camera_position(ship.position.x + camera_distance, midpoint_y,
                       ship.position.z);

  const float camera_terrain_height = get_interpolated_height(
      camera_position.x, camera_position.z, origin_x, origin_z);

  const float TERRAIN_CLEARANCE = 20.0f;

  camera_position.y =
      std::max(camera_position.y, camera_terrain_height + TERRAIN_CLEARANCE);

  const Vec3 look_target(ship.position.x, midpoint_y, ship.position.z);

  return render::create_camera(camera_position, look_target, up);
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
  if (key_state && !key_prev_state) {
    g_orbit_main_view_enabled = !g_orbit_main_view_enabled;
    g_landing_main_view_enabled = g_orbit_main_view_enabled;
  }
  key_prev_state = key_state;
}

bool is_orbit_main_view_enabled() { return g_orbit_main_view_enabled; }

void draw_minimaps(const world::Ship &ship, const world::Planet &earth,
                   const world::Planet &moon, const world::Planet &sun,
                   const render::Camera &game_camera) {
  const int window_width = glutGet(GLUT_WINDOW_WIDTH);
  const int window_height = glutGet(GLUT_WINDOW_HEIGHT);

  // const world::Planet &closest = closest_planet(ship, earth, moon, sun);
  const world::Planet &closest = moon;
  const float closest_distance =
      world::distance_to_surface(closest, ship.position);

  float orbit_half_extent = 1000.0f;
  const moon_scene current_scene = get_moon_scene();
  const bool view_switch_threshold =
      current_scene == MOON_SCENE_SURFACE
          ? closest_distance < EXIT_SURFACE_DISTANCE
          : closest_distance < ENTER_SURFACE_DISTANCE;
  const render::Camera orbit_cam =
      orbit_map_camera(ship, closest, earth, moon, sun, orbit_half_extent);
  update_orbit_trail(ship);

  const MinimapViewport orbit_map = {MINIMAP_MARGINS, MINIMAP_MARGINS, 200,
                                     200};

  const MinimapViewport landing_map = {MINIMAP_MARGINS, MINIMAP_MARGINS, 100,
                                       200};

  if (!view_switch_threshold) {
    if (g_orbit_main_view_enabled) {
      const MinimapViewport full_screen = {0, 0, window_width, window_height};
      setup_viewport(full_screen);

      render::apply_orthographic(orbit_half_extent);
      render::camera_apply(orbit_cam);
      draw_world(ship, earth, moon, sun);
      draw_orbit_trail();
      draw_minimap_ship_marker(ship, orbit_half_extent * 0.03f);

      setup_viewport(orbit_map);
      const float preview_aspect =
          (double)(orbit_map.width) / (double)(orbit_map.height);
      render::apply_perspective(NATURAL_PERSPECTIVE, preview_aspect);
      render::camera_apply(game_camera);
      draw_world(ship, earth, moon, sun);
    } else {
      setup_viewport(orbit_map);
      render::apply_orthographic(orbit_half_extent);
      render::camera_apply(orbit_cam);
      draw_world(ship, earth, moon, sun);
      draw_orbit_trail();
      draw_minimap_ship_marker(ship, orbit_half_extent * 0.03f);
    }
  } else {
    const render::Camera landing_cam = landing_assist_camera(ship, closest);
    if (g_landing_main_view_enabled) {
      const MinimapViewport full_screen = {0, 0, window_width, window_height};
      setup_viewport(full_screen);
      const float aspect = (double)window_width / (double)window_height;
      render::apply_perspective(MINIMAP_1_FOV_DEG, aspect);
      render::camera_apply(landing_cam);
      draw_landing_world(ship, earth, moon, sun);
      draw_minimap_ship_marker(ship, std::max(closest.radius * 0.02f, 2.5f));

      setup_viewport(landing_map);
      const float preview_aspect =
          (double)landing_map.width / (double)landing_map.height;
      render::apply_perspective(NATURAL_PERSPECTIVE, preview_aspect);
      render::camera_apply(game_camera);
      draw_landing_world(ship, earth, moon, sun);
    } else {
      setup_viewport(landing_map);
      const float aspect =
          (double)(landing_map.width) / (double)(landing_map.height);
      render::apply_perspective(MINIMAP_1_FOV_DEG, aspect);
      render::camera_apply(landing_cam);
      draw_landing_world(ship, earth, moon, sun);
      draw_minimap_ship_marker(ship, std::max(closest.radius * 0.02f, 2.5f));
    }
  }

  glViewport(0, 0, window_width, window_height);
  const float main_aspect =
      static_cast<float>(window_width) / static_cast<float>(window_height);
  render::apply_perspective(NATURAL_PERSPECTIVE, main_aspect);
}
} // namespace ui
