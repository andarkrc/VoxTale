#ifndef MODELS_H
#define MODELS_H

#include <stdlib.h>

#include "utils.h"

typedef struct {
	float *data;
	size_t size;
	unsigned int vbo;
	unsigned int vao;
} vbuffer;

vbuffer *model_load_from_obj(char *filename, char *model_name, float r, float g, float b, float a);

vbuffer *model_get_data(char *model_name);

#endif