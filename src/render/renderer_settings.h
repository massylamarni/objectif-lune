#ifndef RENDERER_RENDER_SETTINGS
#define RENDERER_RENDER_SETTINGS

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500
#define SCREEN_POSITION_X 50
#define SCREEN_POSITION_Y 50
#define NATURAL_PERSPECTIVE 60.0f

namespace render {
typedef struct {
  int width;
  int height;
  int pos_x;
  int pos_y;
} screen_settings;

typedef struct {
  bool gl_depth_test_toggle;
  bool gl_lighting_toggle;
  int gl_buffer_bit_mode;
  int gl_polygone_mode;
} render_settings;

typedef struct {
  float fov; // 0.5
  float poly_count; // 16
  float animation_total_speed;
  float animation_speed; // 16
  float rotation_speed;
  bool is_animation_on;
  bool is_rotation_on;
  float camera_speed; // 3
} display_settings;

typedef struct {
  float scene_id;
} scene_property;

typedef struct {
  float scale_value; // 1
} object_property;

typedef struct {
  display_settings ds;
  scene_property sp;
  object_property op;
} model_proprty;

model_proprty init_model_property();
void apply_render_settings(const render_settings *rs);
screen_settings &get_screen_settings();
} // namespace render

#endif
