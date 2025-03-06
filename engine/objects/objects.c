#include "objects.h"

object *object_create(vbuffer *model, texture *text)
{
	object *obj = malloc(sizeof(*obj));
	ASSERT(obj, ERR_MEM_FAIL);

	obj->model = model;
	obj->text = text;

	obj->x = 0.0;
	obj->y = 0.0;
	obj->z = 0.0;

	obj->xrot = 0.0;
	obj->yrot = 0.0;
	obj->zrot = 0.0;

	obj->xscale = 1.0;
	obj->yscale = 1.0;
	obj->zscale = 1.0;

	return obj;
}

object *object_create_at(vbuffer *model, texture *text, float x, float y, float z)
{
	object *obj = malloc(sizeof(*obj));
	ASSERT(obj, ERR_MEM_FAIL);

	obj->model = model;
	obj->text = text;

	obj->x = x;
	obj->y = y;
	obj->z = z;

	obj->xrot = 0.0;
	obj->yrot = 0.0;
	obj->zrot = 0.0;

	obj->xscale = 1.0;
	obj->yscale = 1.0;
	obj->zscale = 1.0;

	return obj;
}