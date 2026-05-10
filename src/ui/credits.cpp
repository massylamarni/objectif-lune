#include "credits.h"

typedef struct {
  const char *title;
  const char *subtitle;
  const char *text;
} CreditEntry;

static const int CREDITS_START_MARGIN = 40;

static const CreditEntry credits[] = {
    {"A Game By", nullptr, "The Moon Project Team"},

    {"Lead Developer", nullptr, "Massyl Amarni"},
    {nullptr, "Core Engine", "Project architecture, core systems, physics"},
    {nullptr, "Rendering",
     "OpenGL based renderer, camera management, textures, minimaps"},
    {nullptr, "World Navigation & Player Movement",
     "Input/output, keybindings"},
    {nullptr, "World Generation",
     "Procedural terrain generation, collision detection"},

    {"Gameplay Concept, 3D Artist & Animation", nullptr, "Rios Quesada Théobald"},
    {nullptr, "Ship Design", "Ship model & animations"},

    {"Technical Artist & UI Designer", nullptr, "Humbert Théo"},
    {nullptr, "Visual Effects", "Explosion model & animation"},
    {nullptr, "Interface Design", "Menus, detailed model viewer"},
    {nullptr, "Environment Art", "Skybox design & scene presentation"},
    {nullptr, "Cinematics", "Start menu scene & animation"},

    {"Special Thanks", nullptr, "You, the player"},
};
static const int credits_count = sizeof(credits) / sizeof(credits[0]);

static float credits_scroll_y = 0.0f;
static float credits_speed = 60.0f;
static const int credits_title_height = 28;
static const int credits_text_height = 22;
static const int credits_gap_height = 18;

static int entry_height(const CreditEntry &e) {
  int h = credits_gap_height * 2;
  if (e.title)
    h += credits_title_height;
  if (e.subtitle)
    h += credits_text_height;
  if (e.text)
    h += credits_text_height;
  return h;
}

void start_credits(bool *show_credits, bool *pause, const float height) {
  *show_credits = true;
  *pause = true;
  credits_scroll_y = -CREDITS_START_MARGIN;
  input::stop_mouse_input(true);
}

void display_credits(const float width, const float height) {
  glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  int cx = (int)(width / 2);
  int y = (int)credits_scroll_y;

  for (int i = 0; i < credits_count; ++i) {
    const CreditEntry &e = credits[i];

    if (y < (int)height && y + entry_height(e) > 0) {
      int line_y = y;
      if (e.title) {
        render::draw_title(e.title, cx - render::measure_title(e.title) / 2,
                           line_y);
        line_y -= credits_title_height;
      }
      if (e.subtitle) {
        render::draw_text(e.subtitle, cx - render::measure_text(e.subtitle) / 2,
                          line_y);
        line_y -= credits_text_height;
      }
      if (e.text) {
        render::draw_text(e.text, cx - render::measure_text(e.text) / 2,
                          line_y);
      }
    }

    y -= entry_height(e);
  }

  render::draw_text("Press r to Restart", 30, 30);
}

void advance_credits(const float dt, bool *show_credits, const float height) {
  credits_scroll_y += credits_speed * dt;

  int total = 0;
  for (int i = 0; i < credits_count; ++i)
    total += entry_height(credits[i]);

  if (credits_scroll_y > total + (int)height + CREDITS_START_MARGIN)
    *show_credits = false;
}