#include "utils.h"

bool toggle_on_key_press(bool *var, char key, char expected_key) {
  if (key == expected_key)
    *var = !(*var);
  return *var;
}

void update_on_key_press(float *var, char key, char inc_key, char dec_key,
                         float min_value, float max_value, float step,
                         bool is_wrapped) {
  if (key == inc_key) {
    if (*var < max_value)
      *var += step;
    else if (is_wrapped)
      *var = min_value;
  } else if (key == dec_key) {
    if (*var > min_value)
      *var -= step;
    else if (is_wrapped)
      *var = max_value;
  }
}

void update_on_key_press_proportional(float *var, char key, char inc_key,
                                      char dec_key, float min_value,
                                      float max_value, float step,
                                      float step_factor, bool is_wrapped) {
  if (key == inc_key) {
    if (*var < max_value)
      *var += fabsf(*var) * step_factor + step;
    else if (is_wrapped)
      *var = min_value;
  } else if (key == dec_key) {
    if (*var > min_value)
      *var -= fabsf(*var) * step_factor + step;
    else if (is_wrapped)
      *var = max_value;
  }
}

/* ------------------- */

void gltoggle_on_key_press(uint macro, char key, char expected_key) {
  if (key == expected_key)
    glIsEnabled(macro) ? glDisable(macro) : glEnable(macro);
}

void gltoggle_macros(uint macros[], size_t macros_len) {
  for (int i = 0; i < macros_len; i++) {
    glIsEnabled(macros[i]) ? glDisable(macros[i]) : glEnable(macros[i]);
  }
}

void glswitch_macros(uint macros[], size_t macros_len,
                     void func(uint var_macro), char key, char inc_key,
                     char dec_key) {
  static uint macro_id = 0;
  if (key == inc_key)
    macro_id += macro_id % macros_len;
  else if (key == dec_key)
    macro_id -= macro_id % macros_len;
  func(macro_id);
};

void glswitch_macros_2p(uint const_macro, uint macros[], size_t macros_len,
                        void func(uint const_macro, uint var_macro), char key,
                        char inc_key, char dec_key) {
  static uint macro_id = 0;
  if (key == inc_key)
    macro_id += macro_id % macros_len;
  else if (key == dec_key)
    macro_id -= macro_id % macros_len;
  func(const_macro, macro_id);
};