
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

typedef struct {
  char key;
  uint macro;
} key_to_macro_map;

typedef struct {
  char key[2];
  uint macros[5];
} key_to_macros_map;

typedef struct {
  char key[2];
  float *fptr;
  float min_value;
  float max_value;
  float step;
  float step_factor;
  bool is_wrapped;
} key_to_float_map;

bool toggle_on_key_press(bool *var, char key, char expected_key);

void update_on_key_press(float *var, char key, char inc_key, char dec_key,
                         float min_value, float max_value, float step,
                         bool is_wrapped);
void update_on_key_press_proportional(float *var, char key, char inc_key,
                                      char dec_key, float min_value,
                                      float max_value, float step,
                                      float step_factor, bool is_wrapped);
/* ------------------- */

void gltoggle_on_key_press(uint macro, char key, char expected_key);
void gltoggle_macros(uint macros[], size_t macros_len);
void glswitch_macros(uint macros[], size_t macros_len,
                     void func(uint var_macro), char key, char inc_key,
                     char dec_key);
void glswitch_macros_2p(uint const_macro, uint macros[], size_t macros_len,
                        void func(uint const_macro, uint var_macro), char key,
                        char inc_key, char dec_key);