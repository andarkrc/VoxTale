#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include "textures.h"
#include "data_structures.h"
#include "error.h"
#include "utils.h"

static hashmap_t *textures_map = NULL;

void texture_destroy(void *data)
{
	free(data);
}

texture *texture_load_rgb(char *filename, char *texture_name)
{

	if (textures_map == NULL)
	{
		textures_map = map_create(texture_destroy);
		stbi_set_flip_vertically_on_load(true);
	}

	texture *text = malloc(sizeof(*text));
	ASSERT(text, ERR_MEM_FAIL);
	unsigned char *data = stbi_load(filename, &text->width, &text->height, &text->channels, 0);
	
	glGenTextures(1, &text->id);
	glBindTexture(GL_TEXTURE_2D, text->id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, text->width, text->height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	

	map_add(textures_map, texture_name, text);

	return text;
}

texture *texture_load_rgba(char *filename, char *texture_name)
{
	if (textures_map == NULL)
	{
		textures_map = map_create(texture_destroy);
		stbi_set_flip_vertically_on_load(true);
	}

	texture *text = malloc(sizeof(*text));
	ASSERT(text, ERR_MEM_FAIL);
	unsigned char *data = stbi_load(filename, &text->width, &text->height, &text->channels, 0);
	
	glGenTextures(1, &text->id);
	glBindTexture(GL_TEXTURE_2D, text->id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, text->width, text->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	map_add(textures_map, texture_name, text);

	return text;
}

texture *texture_get(char *texture_name)
{
	if (textures_map == NULL)
	{
		return NULL;
	}
	return (texture *)map_get(textures_map, texture_name);
}

unsigned int texture_get_id(char *texture_name)
{
	if (textures_map == NULL)
	{
		return (unsigned int)-1;
	}
	texture *text = map_get(textures_map, texture_name);
	if (text == NULL)
	{
		return (unsigned int)-1;
	}
	return text->id;
}

void textures_destroy(void)
{
	map_destroy(textures_map);
}