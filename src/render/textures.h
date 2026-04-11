#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "../../libs/PNG/ChargePngFile.h"

#define TEXTURE_PATH_MAXLEN 64
#define TEXTURES_RELATIVE_PATH "assets/textures"
#define TEXTURE_ID_BUF_LEN 32

namespace render {
typedef enum {
  MOON_TEXTURE,
  EARTH_TEXTURE
} texture_id;

const uint *get_texture_id_buf();
const uint &get_texture_id_buf_len();
void preload_texture_to_gpu(unsigned char *img, int rx, int ry);
void preload_texture(char *file_path);
void free_textures();
void load_textures();
} // namespace render