#include "textures.h"
#include "../output/logs.h"

namespace render {
static uint texture_id_buf[TEXTURE_ID_BUF_LEN];
static uint texture_id_buf_len = 0;

const uint *get_texture_id_buf() { return texture_id_buf; }
const uint &get_texture_id_buf_len() { return texture_id_buf_len; }

void preload_texture_to_gpu(unsigned char *img, int rx, int ry) {
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glGenTextures(1, &texture_id_buf[texture_id_buf_len]);
  glBindTexture(GL_TEXTURE_2D, texture_id_buf[texture_id_buf_len]);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, rx, ry, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  texture_id_buf_len++;
}

/* Preloads texture to RAM then GPU */
void preload_texture(char *file_path) {
  int rx;
  int ry;
  unsigned char *img = chargeImagePng(file_path, &rx, &ry);
  if (img) {
    LOG_RENDER("Loaded texture %s, (%d x %d px), (@%p, %d bytes)", file_path, rx, ry, img, 3*rx*ry);
  } else {
    LOG_RENDER("Failed to load texture %s, (@%p)", file_path, img);
  }
  printf("\n");

  preload_texture_to_gpu(img, rx, ry);
  free(img);
}

void free_textures() {
  for (uint i = 0; i < texture_id_buf_len; i++) {
    glDeleteTextures(1, &texture_id_buf[i]);
  }
  texture_id_buf_len = 0;
}

void load_textures() {
  char texture_dirs[TEXTURE_ID_BUF_LEN][32] = {
    "moon_2k.png",
    "moon_1024.png",
    "texture_LEM.png",
  };
  for (int i = 0; i < 3; i++) {
    char file_path[TEXTURE_PATH_MAXLEN];
    sprintf(file_path, "%s/%s", TEXTURES_RELATIVE_PATH, texture_dirs[i]);
    preload_texture(file_path);
  }
}
} // namespace render
