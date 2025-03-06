#ifndef OBJECTS_H
#define OBJECTS_H

#include <stdio.h>
#include <stdlib.h>
#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include "models.h"
#include "textures.h"
#include "error.h"

extern int window_width;
extern int window_height;

typedef struct
{
	float x, y, z;
	float xrot, yrot, zrot;
	float xscale, yscale, zscale;
	vbuffer *model;
	texture *text;
} object;

object *object_create(vbuffer *model, texture *text);

object *object_create_at(vbuffer *model, texture *text, float x, float y, float z);

void object_draw(object *obj);

#endif