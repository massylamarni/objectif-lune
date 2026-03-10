#include "input.h"

namespace input {
static InputState state;

static int last_mouse_x = 0;
static int last_mouse_y = 0;

void set_mouse_state(int x, int y) {
  state.mouse_position.x = (float)x;
  state.mouse_position.y = (float)y;

  state.mouse_delta.x = (float)(x - last_mouse_x);
  state.mouse_delta.y = (float)(y - last_mouse_y);

  last_mouse_x = x;
  last_mouse_y = y;
}

void set_space_key_state(unsigned char key, int x, int y, int isDown) {
  if (key == ' ') state.space_down = isDown;
}



void keyboard_callback(unsigned char key, int x, int y) {
  // printf("K  %4d %4d %4d\n",specialKey,x,y); 

}

void keyboard_up_callback(unsigned char key, int x, int y) {
  // printf("KUP  %4d %4d %4d\n",specialKey,x,y); 

}

void special_callback(int specialKey, int x, int y) {
  // printf("S  %4d %4d %4d\n",specialKey,x,y);

}

void mouse_callback(int button, int state, int x, int y) {
  // printf("M  %4d %4d %4d %4d\n",button,state,x,y);
  
}

void mouse_motion_callback(int x, int y) {
  // printf("MM %4d %4d\n",x,y);

}

void mouse_passive_motion_callback(int x, int y) {
  // printf("PM %4d %4d\n",x,y);

}

void input_init() {
  state.mouse_position = Vec2(0, 0);
  state.mouse_delta = Vec2(0, 0);
  state.space_down = false;

  glutKeyboardFunc(keyboard_callback);
  glutKeyboardUpFunc(keyboard_up_callback);
  glutSpecialFunc(special_callback);
  glutMouseFunc(mouse_callback);
  glutMotionFunc(mouse_motion_callback);
  glutPassiveMotionFunc(mouse_passive_motion_callback);

}

void input_update() { state.mouse_delta = Vec2(0, 0); }

const InputState &input_get_state() { return state; }

} // namespace input