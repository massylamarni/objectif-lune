#ifndef INPUT_KEYBOARD
#define INPUT_KEYBOARD

#include "../../src/math/vec2.h"
#include "../render/renderer_settings.h"
#include "utils.h"

namespace input {
void set_global_keyboard_listeners(unsigned char key, int x, int y,
                                   render::model_proprty mp);
void set_global_keyboard_listeners_s(unsigned char key, int x, int y,
                                     render::model_proprty mp);
void input_init_keyboard();
} // namespace input

#endif