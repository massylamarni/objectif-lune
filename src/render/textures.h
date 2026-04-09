#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "../../libs/PNG/ChargePngFile.h"

#define TEXTURES_RELATIVE_PATH "assets/textures"

namespace render {
const uint *get_texture_id_buf();
const uint &get_texture_id_buf_len();
void preload_texture_to_gpu(unsigned char *img, int rx, int ry);
void preload_texture(char *file_path);
void free_textures();
void load_all_emoji_textures_example();
} // namespace render