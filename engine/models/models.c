#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <string.h>

#include "models.h"
#include "error.h"
#include "data_structures.h"

static hashmap_t *model_map = NULL;

vbuffer *vbuffer_create(void)
{
	vbuffer *buff = malloc(sizeof(*buff));
	buff->data = malloc(sizeof(float) * 12);
	buff->size = 12;

	return buff;
}

void vbuffer_destroy(void *data)
{
	vbuffer *vbuff = data;
	free(vbuff->data);
	free(vbuff);
}

vbuffer *model_load_from_obj(char *filename, char *model_name)
{
	FILE *file = fopen(filename, "rt");
	ASSERT(file, ERR_FILE_OPEN);

	list_t *x = list_create(NULL);
	list_t *y = list_create(NULL);
	list_t *z = list_create(NULL);

	list_t *u = list_create(NULL);
	list_t *v = list_create(NULL);

	list_t *nx = list_create(NULL);
	list_t *ny = list_create(NULL);
	list_t *nz = list_create(NULL);

	vbuffer *vbuff = vbuffer_create();
	int vertex_number = 0;

	char line[1024];

	while (read_line(file, line) != -1)
	{
		if (strlen(line) == 0)
		{
			continue;
		}
		char *terms[100];
		int i = 1;
		terms[0] = strtok(line, " ");
		while ((terms[i] = strtok(NULL, " ")))
		{
			i++;
		}

		if (strcmp(terms[0], "v") == 0)
		{
			float xx = atof(terms[1]);
			float yy = atof(terms[2]);
			float zz = atof(terms[3]);

			list_push(x, float_to_void(xx));
			list_push(y, float_to_void(yy));
			list_push(z, float_to_void(zz));
		}
		else if (strcmp(terms[0], "vn") == 0)
		{
			float nxx = atof(terms[1]);
			float nyy = atof(terms[2]);
			float nzz = atof(terms[3]);

			list_push(nx, float_to_void(nxx));
			list_push(ny, float_to_void(nyy));
			list_push(nz, float_to_void(nzz));
		}
		else if (strcmp(terms[0], "vt") == 0)
		{
			float uu = atof(terms[1]);
			float vv = atof(terms[2]);

			list_push(u, float_to_void(uu));
			list_push(v, float_to_void(vv));
		}
		else if (strcmp(terms[0], "f") == 0)
		{
			char *data[3];
			vertex_number += 3;
			vbuff->data = realloc(vbuff->data, vertex_number * sizeof(float) * 12);
			ASSERT(vbuff->data, ERR_MEM_FAIL);
			vbuff->size = vertex_number;
			for (int i = 1; i <= 3; i++)
			{
				data[0] = strtok(terms[i], "/");
				data[1] = strtok(NULL, "/");
				data[2] = strtok(NULL, "/");
				int pos_index = atoi(data[0]) - 1;
				int uv_index = atoi(data[1]) - 1;
				int norm_index = atoi(data[2]) - 1;

				float xx = void_to_float(list_get(x, pos_index));
				float yy = void_to_float(list_get(y, pos_index));
				float zz = void_to_float(list_get(z, pos_index));

				float uu = void_to_float(list_get(u, uv_index));
				float vv = void_to_float(list_get(v, uv_index));

				float nxx = void_to_float(list_get(nx, norm_index));
				float nyy = void_to_float(list_get(ny, norm_index));
				float nzz = void_to_float(list_get(nz, norm_index));

				vbuff->data[(vertex_number - 3 + i - 1) * 12 + 0] = xx;
				vbuff->data[(vertex_number - 3 + i - 1) * 12 + 1] = yy;
				vbuff->data[(vertex_number - 3 + i - 1) * 12 + 2] = zz;

				vbuff->data[(vertex_number - 3 + i - 1) * 12 + 3] = uu;
				vbuff->data[(vertex_number - 3 + i - 1) * 12 + 4] = vv;

				vbuff->data[(vertex_number - 3 + i - 1) * 12 + 5] = nxx;
				vbuff->data[(vertex_number - 3 + i - 1) * 12 + 6] = nyy;
				vbuff->data[(vertex_number - 3 + i - 1) * 12 + 7] = nzz;

				vbuff->data[(vertex_number - 3 + i - 1) * 12 + 8] = 1.0f;
				vbuff->data[(vertex_number - 3 + i - 1) * 12 + 9] = 1.0f;
				vbuff->data[(vertex_number - 3 + i - 1) * 12 + 10] = 1.0f;
				vbuff->data[(vertex_number - 3 + i - 1) * 12 + 11] = 1.0f;
			}
		}
	}

	list_destroy(x);
	list_destroy(y);
	list_destroy(z);

	list_destroy(u);
	list_destroy(v);

	list_destroy(nx);
	list_destroy(ny);
	list_destroy(nz);

	glGenBuffers(1, &vbuff->vbo);
	glGenVertexArrays(1, &vbuff->vao);

	glBindVertexArray(vbuff->vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbuff->vbo);
	glBufferData(GL_ARRAY_BUFFER, vbuff->size * sizeof(float) * 12, vbuff->data, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void *)0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void *)(8 * sizeof(float)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void *)(5 * sizeof(float)));
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	fclose(file);


	if (model_map == NULL)
	{
		model_map = map_create(vbuffer_destroy);
	}

	map_add(model_map, model_name, vbuff);

	return vbuff;
}

vbuffer *model_load_from_obj_color(char *filename, char *model_name, float r, float g, float b, float a)
{
	FILE *file = fopen(filename, "rt");
	ASSERT(file, ERR_FILE_OPEN);

	list_t *x = list_create(NULL);
	list_t *y = list_create(NULL);
	list_t *z = list_create(NULL);

	list_t *u = list_create(NULL);
	list_t *v = list_create(NULL);

	list_t *nx = list_create(NULL);
	list_t *ny = list_create(NULL);
	list_t *nz = list_create(NULL);

	vbuffer *vbuff = vbuffer_create();
	int vertex_number = 0;

	char line[1024];

	while (read_line(file, line) != -1)
	{
		if (strlen(line) == 0)
		{
			continue;
		}
		char *terms[100];
		int i = 1;
		terms[0] = strtok(line, " ");
		while ((terms[i] = strtok(NULL, " ")))
		{
			i++;
		}

		if (strcmp(terms[0], "v") == 0)
		{
			float xx = atof(terms[1]);
			float yy = atof(terms[2]);
			float zz = atof(terms[3]);

			list_push(x, float_to_void(xx));
			list_push(y, float_to_void(yy));
			list_push(z, float_to_void(zz));
		}
		else if (strcmp(terms[0], "vn") == 0)
		{
			float nxx = atof(terms[1]);
			float nyy = atof(terms[2]);
			float nzz = atof(terms[3]);

			list_push(nx, float_to_void(nxx));
			list_push(ny, float_to_void(nyy));
			list_push(nz, float_to_void(nzz));
		}
		else if (strcmp(terms[0], "vt") == 0)
		{
			float uu = atof(terms[1]);
			float vv = atof(terms[2]);

			list_push(u, float_to_void(uu));
			list_push(v, float_to_void(vv));
		}
		else if (strcmp(terms[0], "f") == 0)
		{
			char *data[3];
			vertex_number += 3;
			vbuff->data = realloc(vbuff->data, vertex_number * sizeof(float) * 12);
			ASSERT(vbuff->data, ERR_MEM_FAIL);
			vbuff->size = vertex_number;
			for (int i = 1; i <= 3; i++)
			{
				data[0] = strtok(terms[i], "/");
				data[1] = strtok(NULL, "/");
				data[2] = strtok(NULL, "/");
				int pos_index = atoi(data[0]) - 1;
				int uv_index = atoi(data[1]) - 1;
				int norm_index = atoi(data[2]) - 1;

				float xx = void_to_float(list_get(x, pos_index));
				float yy = void_to_float(list_get(y, pos_index));
				float zz = void_to_float(list_get(z, pos_index));

				float uu = void_to_float(list_get(u, uv_index));
				float vv = void_to_float(list_get(v, uv_index));

				float nxx = void_to_float(list_get(nx, norm_index));
				float nyy = void_to_float(list_get(ny, norm_index));
				float nzz = void_to_float(list_get(nz, norm_index));

				vbuff->data[(vertex_number - 3 + i - 1) * 12 + 0] = xx;
				vbuff->data[(vertex_number - 3 + i - 1) * 12 + 1] = yy;
				vbuff->data[(vertex_number - 3 + i - 1) * 12 + 2] = zz;

				vbuff->data[(vertex_number - 3 + i - 1) * 12 + 3] = uu;
				vbuff->data[(vertex_number - 3 + i - 1) * 12 + 4] = vv;

				vbuff->data[(vertex_number - 3 + i - 1) * 12 + 5] = nxx;
				vbuff->data[(vertex_number - 3 + i - 1) * 12 + 6] = nyy;
				vbuff->data[(vertex_number - 3 + i - 1) * 12 + 7] = nzz;

				vbuff->data[(vertex_number - 3 + i - 1) * 12 + 8] = r;
				vbuff->data[(vertex_number - 3 + i - 1) * 12 + 9] = g;
				vbuff->data[(vertex_number - 3 + i - 1) * 12 + 10] = b;
				vbuff->data[(vertex_number - 3 + i - 1) * 12 + 11] = a;
			}
		}
	}

	list_destroy(x);
	list_destroy(y);
	list_destroy(z);

	list_destroy(u);
	list_destroy(v);

	list_destroy(nx);
	list_destroy(ny);
	list_destroy(nz);

	glGenBuffers(1, &vbuff->vbo);
	glGenVertexArrays(1, &vbuff->vao);

	glBindVertexArray(vbuff->vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbuff->vbo);
	glBufferData(GL_ARRAY_BUFFER, vbuff->size * sizeof(float) * 12, vbuff->data, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void *)0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void *)(8 * sizeof(float)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void *)(5 * sizeof(float)));
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	fclose(file);


	if (model_map == NULL)
	{
		model_map = map_create(vbuffer_destroy);
	}

	map_add(model_map, model_name, vbuff);

	return vbuff;
}

vbuffer *model_get_data(char *model_name)
{
	if (model_map == NULL)
	{
		return NULL;
	}
	return map_get(model_map, model_name);
}

void models_destroy(void)
{
	map_destroy(model_map);
}