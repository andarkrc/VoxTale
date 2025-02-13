#ifndef MODELS_H
#define MODELS_H

#include <stdlib.h>

#include "utils.h"

typedef struct {
	float *data;
	size_t size;
	unsigned int vao;
} vbuffer;

vbuffer *model_load_from_obj(char *filename, color_t color);

#endif