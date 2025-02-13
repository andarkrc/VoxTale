#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include "models.h"
#include "error.h"

vbuffer *vbuffer_create(size_t vertex_number)
{
	vbuffer *buff = malloc(sizeof(*buff));
	buff->data = malloc(sizeof(float) * 12 * vertex_number);
	buff->size = 12 * vertex_number;

	return buff;
}

vbuffer model_load_from_object(char *filename, color_t color)
{
	
}