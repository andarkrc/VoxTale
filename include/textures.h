#ifndef TEXTURES_H
#define TEXTURES_H

#include <stdlib.h>

#include "stb_image.h"

typedef struct {
	unsigned int id;
	int width;
	int height;
	int channels;
} texture;

texture *texture_load_rgb(char *filename, char *texture_name);
texture *texture_load_rgba(char *filename, char *texture_name);

texture *texture_get(char *texture_name);
unsigned int texture_get_id(char *texture_name);

void textures_destroy(void);

#endif