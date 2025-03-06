#ifndef VOXEL_H
#define VOXEL_H

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "error.h"
#include "models.h"

typedef union voxel_model
{
	vbuffer *face[6];
	struct
	{
		vbuffer *face0;
		vbuffer *face1;
		vbuffer *face2;
		vbuffer *face3;
		vbuffer *face4;
		vbuffer *face5;
	};
} voxel_model;

voxel_model *voxel_get_default(void);

#endif