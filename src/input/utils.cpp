#include "utils.h"

void toggle_on_key_press(bool *var, char key, char expected_key) {
  if (key == expected_key)
    *var = !(*var);
}

void update_on_key_press_i(int *var, char key, char inc_key, char dec_key,
                           int min_value, int max_value, float step) {
  if (key == inc_key && *var < max_value)
    *var += step;
  else if (key == dec_key && *var > min_value)
    *var -= step;
}

void update_on_key_press_f(float *var, char key, char inc_key, char dec_key,
                           float min_value, float max_value, float step) {
  if (key == inc_key && *var < max_value)
    *var += step;
  else if (key == dec_key && *var > min_value)
    *var -= step;
}

void update_on_key_press_wrapped_i(int *var, char key, char inc_key,
                                   char dec_key, int min_value, int max_value,
                                   int step) {
  if (key == inc_key) {
    if (*var < max_value)
      *var += step;
    else
      *var = min_value;
  } else if (key == dec_key) {
    if (*var > min_value)
      *var -= step;
    else
      *var = max_value;
  }
}

void update_on_key_press_wrapped_f(float *var, char key, char inc_key,
                                   char dec_key, float min_value,
                                   float max_value, float step) {
  if (key == inc_key) {
    if (*var < max_value)
      *var += step;
    else
      *var = min_value;
  } else if (key == dec_key) {
    if (*var > min_value)
      *var -= step;
    else
      *var = max_value;
  }
}

void update_on_key_press_proportional_f(float *var, char key, char inc_key,
                                        char dec_key, float min_value,
                                        float max_value, float step,
                                        float step_factor) {
  if (key == inc_key && *var < max_value)
    *var += fabsf(*var) * step_factor + step;
  else if (key == dec_key && *var > min_value)
    *var -= fabsf(*var) * step_factor + step;
}

void update_on_key_press_proportional_wrapped_f(float *var, char key,
                                                char inc_key, char dec_key,
                                                float min_value,
                                                float max_value, float step,
                                                float step_factor) {
  if (key == inc_key) {
    if (*var < max_value)
      *var += fabsf(*var) * step_factor + step;
    else
      *var = min_value;
  } else if (key == dec_key) {
    if (*var > min_value)
      *var -= fabsf(*var) * step_factor + step;
    else
      *var = max_value;
  }
}

/* ------------------- */

void gltoggle_on_key_press(int macro, char key, char expected_key) {
  if (key == expected_key)
    glIsEnabled(macro) ? glDisable(macro) : glEnable(macro);
}

void gltoggle_macro(int macro) {
  glIsEnabled(macro) ? glDisable(macro) : glEnable(macro);
}

void gltoggle_macros(int macros[]) {
  for (int i = 0; i < MACROS_ARR_LEN; i++) {
    if (macros[i] != 0) gltoggle_macro(macros[i]);
  }
}

void gltoggle_macro_custom_1p(int macro, void func(int var_macro)) {
  
};
void gltoggle_macros_custom_1p(int macros[], void func(int var_macro));
void gltoggle_macro_custom_2p(int macro, void func(int const_macro, int var_macro));
void gltoggle_macros_custom_2p(int macros[], void func(int const_macro, int var_macro));