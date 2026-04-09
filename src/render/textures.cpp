#include "textures.h"

namespace render {
static uint texture_id_buf[32];
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
  printf("%s\n", file_path);
  unsigned char *img = chargeImagePng(file_path, &rx, &ry);
  if (img) {
    printf("Resolution en x : %8d\n", rx);
    printf("Resolution en y : %8d\n", ry);
    printf("Adresse         : %p, %d octets\n", img, 3 * rx * ry);
  } else {
    printf("Adresse         : %p\n", img);
  }
  printf("\n");

  preload_texture_to_gpu(img, rx, ry);
  free(img);
}

void free_textures() {
  for (int i = 0; i < texture_id_buf_len; i++) {
    glDeleteTextures(1, &texture_id_buf[i]);
  }
  texture_id_buf_len = 0;
}

void load_all_emoji_textures_example() {
  for (int i = 1; i <= 6; i++) {
    char file_path[32];
    sprintf(file_path, "%s/emojis/emoji%i.png", TEXTURES_RELATIVE_PATH, i);
    preload_texture(file_path);
  }
}
} // namespace render