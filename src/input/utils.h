
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

#define MACROS_ARR_LEN 9

void toggle_on_key_press(bool *var, char key, char expected_key);
void update_on_key_press_i(int *var, char key, char inc_key, char dec_key,
                           int min_value, int max_value, float step);
void update_on_key_press_f(float *var, char key, char inc_key, char dec_key,
                           float min_value, float max_value, float step);
void update_on_key_press_wrapped_i(int *var, char key, char inc_key,
                                   char dec_key, int min_value, int max_value,
                                   int step);
void update_on_key_press_wrapped_f(float *var, char key, char inc_key,
                                   char dec_key, float min_value,
                                   float max_value, float step);
void update_on_key_press_proportional_f(float *var, char key, char inc_key,
                                        char dec_key, float min_value,
                                        float max_value, float step,
                                        float step_factor);
void update_on_key_press_proportional_wrapped_f(float *var, char key,
                                                char inc_key, char dec_key,
                                                float min_value,
                                                float max_value, float step,
                                                float step_factor);
void gltoggle_on_key_press(int macro, char key, char expected_key);
void gltoggle_macro(int macro);
void gltoggle_macros(int macros[]);
void gltoggle_macro_custom_1p(int macro, void func(int var_macro));
void gltoggle_macros_custom_1p(int macros[], void func(int var_macro));
void gltoggle_macro_custom_2p(int macro, void func(int const_macro, int var_macro));
void gltoggle_macros_custom_2p(int macros[], void func(int const_macro, int var_macro));