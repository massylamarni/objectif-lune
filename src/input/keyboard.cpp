#include "keyboard.h"

/*
'h' GL_DEPTH_TEST
'H' GL_CULL_FACE
'l' GL_LIGHTING
'L' GL_COLOR_MATERIAL
'?' GL_LIGHTING
'P' GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, GL_DEPTH_BUFFER_BIT, GL_COLOR_BUFFER_BIT
'p' GL_FILL, GL_LINE, GL_POINT
*/

/*
  update_on_key_press_f (&prst_size, key, 'N', 'n', 0.01F, 10.0F, 0.01F);
  update_on_key_press_f (&prst_fov, key, 'B', 'b', 0.0F, 4.4F, 0.1F);
  update_on_key_press_i (&prst_nbPolygon, key, 'M', 'm', 3, 1024);
*/

static const int key_map[] = {

};

void set_global_keyboard_listeners(unsigned char key, int x, int y) {

}