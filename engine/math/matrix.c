#include <stdlib.h>

#include "matrix.h"
#include "error.h"

mat4 *mat4_create(void)
{
	mat4 *mat = malloc(sizeof(*mat));
	ASSERT(mat, ERR_MEM_FAIL);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mat->val[i][j] = 0.0;
		}
	}

	return mat;
}

void mat4_destroy(mat4 *mat)
{
	free(mat);
}

vec4 *vec4_create(float x, float y, float z, float w)
{
	vec4 *vec = malloc(sizeof(*vec));
	ASSERT(vec, ERR_MEM_FAIL);

	vec->val[0] = x;
	vec->val[1] = y;
	vec->val[2] = z;
	vec->val[3] = w;

	return vec;
}

void vec4_destroy(vec4 *vec)
{
	free(vec);
}

vec3 *vec3_create(float x, float y, float z)
{
	vec3 *vec = malloc(sizeof(*vec));
	ASSERT(vec, ERR_MEM_FAIL);

	vec->val[0] = x;
	vec->val[1] = y;
	vec->val[2] = z;

	return vec;
}

void vec3_destroy(vec3 *vec)
{
	free(vec);
}

vec4 *vec4_from_vec3(vec3 *vec)
{
	return vec4_create(
		vec->val[0],
		vec->val[1],
		vec->val[2],
		1.0
		);
}

vec3 *vec3_from_vec4(vec4 *vec)
{
	return vec3_create(
		vec->val[0],
		vec->val[1],
		vec->val[2]
		);
}

mat4 *mat4_null(void)
{
	return mat4_create();
}

mat4 *mat4_identity(void)
{
	mat4 *mat = mat4_create();
	
	for (int i = 0; i < 4; i++)
	{
		mat->val[i][i] = 1.0;
	}

	return mat;
}

mat4 *mat4_add(mat4 *matrix1, mat4 *matrix2)
{
	mat4 *mat = mat4_create();

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mat->val[i][j] = matrix1->val[i][j] + matrix2->val[i][j];
		}
	}

	mat4_destroy(matrix1);
	mat4_destroy(matrix2);

	return mat;
}

mat4 *mat4_sub(mat4 *matrix1, mat4 *matrix2)
{
	mat4 *mat = mat4_create();

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mat->val[i][j] = matrix1->val[i][j] - matrix2->val[i][j];
		}
	}

	mat4_destroy(matrix1);
	mat4_destroy(matrix2);

	return mat;
}

mat4 *mat4_mul(mat4 *matrix1, mat4 *matrix2)
{
	mat4 *mat = mat4_create();

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mat->val[j][i] = 0.0;
			for (int k = 0; k < 4; k++)
			{
				mat->val[j][i] += matrix1->val[k][i] * matrix2->val[j][k];
			}
		}
	}

	mat4_destroy(matrix1);
	mat4_destroy(matrix2);

	return mat;
}

mat4 *mat4_addc(mat4 *matrix1, mat4 *matrix2)
{
	mat4 *mat = mat4_create();

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mat->val[i][j] = matrix1->val[i][j] + matrix2->val[i][j];
		}
	}

	return mat;
}

mat4 *mat4_subc(mat4 *matrix1, mat4 *matrix2)
{
	mat4 *mat = mat4_create();

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mat->val[i][j] = matrix1->val[i][j] - matrix2->val[i][j];
		}
	}

	return mat;
}

mat4 *mat4_mulc(mat4 *matrix1, mat4 *matrix2)
{
	mat4 *mat = mat4_create();

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mat->val[j][i] = 0.0;
			for (int k = 0; k < 4; k++)
			{
				mat->val[j][i] += matrix1->val[k][i] * matrix2->val[j][k];
			}
		}
	}

	return mat;
}

mat4 *mat4_smul(mat4 *matrix, float scalar)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			matrix->val[i][j] *= scalar;
		}
	}

	return matrix;
}

mat4 *mat4_dup(mat4 *matrix)
{
	mat4 *mat = mat4_create();

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mat->val[i][j] = matrix->val[i][j];
		}
	}

	return mat;
}

float mat4_det(mat4 *m)
{
	return
		m->val[0][3] * m->val[1][2] * m->val[2][1] * m->val[3][0] - m->val[0][2] * m->val[1][3] * m->val[2][1] * m->val[3][0] -
		m->val[0][3] * m->val[1][1] * m->val[2][2] * m->val[3][0] + m->val[0][1] * m->val[1][3] * m->val[2][2] * m->val[3][0] +
		m->val[0][2] * m->val[1][1] * m->val[2][3] * m->val[3][0] - m->val[0][1] * m->val[1][2] * m->val[2][3] * m->val[3][0] -
		m->val[0][3] * m->val[1][2] * m->val[2][0] * m->val[3][1] + m->val[0][2] * m->val[1][3] * m->val[2][0] * m->val[3][1] +
		m->val[0][3] * m->val[1][0] * m->val[2][2] * m->val[3][1] - m->val[0][0] * m->val[1][3] * m->val[2][2] * m->val[3][1] -
		m->val[0][2] * m->val[1][0] * m->val[2][3] * m->val[3][1] + m->val[0][0] * m->val[1][2] * m->val[2][3] * m->val[3][1] +
		m->val[0][3] * m->val[1][1] * m->val[2][0] * m->val[3][2] - m->val[0][1] * m->val[1][3] * m->val[2][0] * m->val[3][2] -
		m->val[0][3] * m->val[1][0] * m->val[2][1] * m->val[3][2] + m->val[0][0] * m->val[1][3] * m->val[2][1] * m->val[3][2] +
		m->val[0][1] * m->val[1][0] * m->val[2][3] * m->val[3][2] - m->val[0][0] * m->val[1][1] * m->val[2][3] * m->val[3][2] -
		m->val[0][2] * m->val[1][1] * m->val[2][0] * m->val[3][3] + m->val[0][1] * m->val[1][2] * m->val[2][0] * m->val[3][3] +
		m->val[0][2] * m->val[1][0] * m->val[2][1] * m->val[3][3] - m->val[0][0] * m->val[1][2] * m->val[2][1] * m->val[3][3] -
		m->val[0][1] * m->val[1][0] * m->val[2][2] * m->val[3][3] + m->val[0][0] * m->val[1][1] * m->val[2][2] * m->val[3][3];
}

mat4 *mat4_rotatexr(float angle)
{
	mat4 *mat = mat4_identity();

	mat->val[1][1] = cos(angle);
	mat->val[2][1] = -sin(angle);
	mat->val[1][2] = sin(angle);
	mat->val[2][2] = cos(angle);

	return mat;
}

mat4 *mat4_rotateyr(float angle)
{
	mat4 *mat = mat4_identity();

	mat->val[0][0] = cos(angle);
	mat->val[2][0] = sin(angle);
	mat->val[0][2] = -sin(angle);
	mat->val[2][2] = cos(angle); 

	return mat;
}

mat4 *mat4_rotatezr(float angle)
{
	mat4 *mat = mat4_identity();

	mat->val[0][0] = cos(angle);
	mat->val[1][0] = -sin(angle);
	mat->val[0][1] = sin(angle);
	mat->val[2][2] = cos(angle);

	return mat;
}

mat4 *mat4_rotatexd(float angle)
{
	angle = angle * M_PI / 180;
	mat4 *mat = mat4_identity();

	mat->val[1][1] = cos(angle);
	mat->val[2][1] = -sin(angle);
	mat->val[1][2] = sin(angle);
	mat->val[2][2] = cos(angle);

	return mat;
}

mat4 *mat4_rotateyd(float angle)
{
	angle = angle * M_PI / 180;
	mat4 *mat = mat4_identity();

	mat->val[0][0] = cos(angle);
	mat->val[2][0] = sin(angle);
	mat->val[0][2] = -sin(angle);
	mat->val[2][2] = cos(angle); 

	return mat;
}

mat4 *mat4_rotatezd(float angle)
{
	angle = angle * M_PI / 180;
	mat4 *mat = mat4_identity();

	mat->val[0][0] = cos(angle);
	mat->val[1][0] = -sin(angle);
	mat->val[0][1] = sin(angle);
	mat->val[2][2] = cos(angle);

	return mat;
}

mat4 *mat4_translate(float x, float y, float z)
{
	mat4 *mat = mat4_identity();
	
	mat->val[3][0] = x;
	mat->val[3][1] = y; // these might need to be negated
	mat->val[3][2] = z;

	return mat;
}

mat4 *mat4_scale(float x, float y, float z)
{
	mat4 *mat = mat4_identity();
	
	mat->val[0][0] = x;
	mat->val[1][1] = y;
	mat->val[2][2] = z;

	return mat;
}

mat4 *mat4_transpose(mat4 *matrix)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			float aux = matrix->val[i][j];
			matrix->val[i][j] = matrix->val[j][i];
			matrix->val[j][i] = aux;
		}
	}

	return matrix;
}

mat4 *mat4_ortho(float left, float right, float bottom, float top, float znear, float zfar)
{
	mat4 *mat = mat4_identity();

	mat->val[0][0] = 2.0 / (right - left);
	mat->val[1][1] = 2.0 / (top - bottom);
	mat->val[2][2] = -2.0 / (zfar - znear);
	mat->val[3][0] = - (right + left) / (right - left);
	mat->val[3][1] = - (top + bottom) / (top - bottom);
	mat->val[3][2] = - (zfar + znear) / (zfar - znear);

	return mat;
}

mat4 *mat4_perspective(float fovy, float aspect, float znear, float zfar)
{
	mat4 *mat = mat4_identity();
	
	float tanfovy = tan(fovy / 2.0);
	mat->val[0][0] = 1.0 / (aspect * tanfovy);
	mat->val[1][1] = 1.0 / tanfovy;
	mat->val[2][2] = -(zfar + znear) / (zfar - znear);
	mat->val[2][3] = -1.0;
	mat->val[3][2] = -(2.0 * zfar * znear) / (zfar - znear);

	return mat;
}

mat4 *mat4_lookat(vec3 *pos, vec3 *target, vec3 *up)
{
	vec3 *forward = vec3_norm(vec3_subc(target, pos));
	vec3 *right = vec3_norm(vec3_crossc(forward, up));
	vec3 *reup = vec3_crossc(right, forward);

	mat4 *mat = mat4_identity();

	mat->val[0][0] = right->x;
	mat->val[1][0] = right->y;
	mat->val[2][0] = right->z;
	mat->val[0][1] = reup->x;
	mat->val[1][1] = reup->y;
	mat->val[2][1] = reup->z;
	mat->val[0][2] = -(forward->x);
	mat->val[1][2] = -(forward->y);
	mat->val[2][2] = -(forward->z);

	mat->val[3][0] = -vec3_dot(pos, right);
	mat->val[3][1] = -vec3_dot(pos, reup);
	mat->val[3][2] = vec3_dot(pos, forward);

	vec3_destroy(forward);
	vec3_destroy(right);
	vec3_destroy(reup);
	vec3_destroy(pos);
	vec3_destroy(target);
	vec3_destroy(up);

	return mat;
}

mat4 *mat4_lookatc(vec3 *pos, vec3 *target, vec3 *up)
{
	vec3 *forward = vec3_norm(vec3_subc(target, pos));
	vec3 *right = vec3_norm(vec3_crossc(forward, up));
	vec3 *reup = vec3_crossc(right, forward);

	mat4 *mat = mat4_identity();

	mat->val[0][0] = right->x;
	mat->val[1][0] = right->y;
	mat->val[2][0] = right->z;
	mat->val[0][1] = reup->x;
	mat->val[1][1] = reup->y;
	mat->val[2][1] = reup->z;
	mat->val[0][2] = -(forward->x);
	mat->val[1][2] = -(forward->y);
	mat->val[2][2] = -(forward->z);

	mat->val[3][0] = -vec3_dot(pos, right);
	mat->val[3][1] = -vec3_dot(pos, reup);
	mat->val[3][2] = vec3_dot(pos, forward);

	vec3_destroy(forward);
	vec3_destroy(right);
	vec3_destroy(reup);

	return mat;
}

vec4 *vec4_matmulc(mat4 *matrix, vec4 *vector)
{
	 vec4 *result = vec4_create(0., 0., 0., 0.);

	 for (int i = 0; i < 4; i++)
	 {
	 	result->val[i] = 0.0;
	 	for (int j = 0; j < 4; j++)
	 	{
	 		result->val[i] += vector->val[j] * matrix->val[j][i];
	 	}
	 }

	 return result;
}

vec4 *vec4_matmul(mat4 *matrix, vec4 *vector)
{
	 vec4 *result = vec4_create(0., 0., 0., 0.);

	 for (int i = 0; i < 4; i++)
	 {
	 	result->val[i] = 0.0;
	 	for (int j = 0; j < 4; j++)
	 	{
	 		result->val[i] += vector->val[j] * matrix->val[j][i];
	 	}
	 }

	 mat4_destroy(matrix);
	 vec4_destroy(vector);

	 return result;
}

vec4 *vec4_add(vec4 *vector1, vec4 *vector2)
{
	vec4 *vec = vec4_create(
					vector1->val[0] + vector2->val[0],
					vector1->val[1] + vector2->val[1],
					vector1->val[2] + vector2->val[2],
					vector1->val[3] + vector2->val[3]
				);

	vec4_destroy(vector1);
	vec4_destroy(vector2);

	return vec;
}

vec4 *vec4_sub(vec4 *vector1, vec4 *vector2)
{
	vec4 *vec = vec4_create(
					vector1->val[0] - vector2->val[0],
					vector1->val[1] - vector2->val[1],
					vector1->val[2] - vector2->val[2],
					vector1->val[3] - vector2->val[3]
				);

	vec4_destroy(vector1);
	vec4_destroy(vector2);

	return vec;
}

vec4 *vec4_addc(vec4 *vector1, vec4 *vector2)
{
	return vec4_create(
					vector1->val[0] + vector2->val[0],
					vector1->val[1] + vector2->val[1],
					vector1->val[2] + vector2->val[2],
					vector1->val[3] + vector2->val[3]
				);
}

vec4 *vec4_subc(vec4 *vector1, vec4 *vector2)
{
	return vec4_create(
					vector1->val[0] - vector2->val[0],
					vector1->val[1] - vector2->val[1],
					vector1->val[2] - vector2->val[2],
					vector1->val[3] - vector2->val[3]
				);
}

float vec4_dot(vec4 *vector1, vec4 *vector2)
{
	float result = 0.0;

	for (int i = 0; i < 4; i++)
	{
		result += vector1->val[i] * vector2->val[i];
	}

	return result;
}

vec4 *vec4_crossxyz(vec4 *vec1, vec4 *vec2)
{
	vec4 *vec = vec4_create(
		vec1->y * vec2->z - vec1->z * vec2->y,
		vec1->z * vec2->x - vec1->x * vec2->z,
		vec1->x * vec2->y - vec1->y * vec2->x,
		1.0
		);

	vec4_destroy(vec1);
	vec4_destroy(vec2);

	return vec;
}

vec4 *vec4_crossxyzc(vec4 *vec1, vec4 *vec2)
{
	return vec4_create(
		vec1->y * vec2->z - vec1->z * vec2->y,
		vec1->z * vec2->x - vec1->x * vec2->z,
		vec1->x * vec2->y - vec1->y * vec2->x,
		1.0
		);
}

vec3 *vec3_add(vec3 *vector1, vec3 *vector2)
{
	vec3 *vec = vec3_create(
					vector1->x + vector2->x,
					vector1->y + vector2->y,
					vector1->z + vector2->z
				);

	vec3_destroy(vector1);
	vec3_destroy(vector2);

	return vec;
}

vec3 *vec3_sub(vec3 *vector1, vec3 *vector2)
{
	vec3 *vec = vec3_create(
					vector1->x - vector2->x,
					vector1->y - vector2->y,
					vector1->z - vector2->z
				);

	vec3_destroy(vector1);
	vec3_destroy(vector2);

	return vec;
}

vec3 *vec3_addc(vec3 *vector1, vec3 *vector2)
{
	return vec3_create(
					vector1->x + vector2->x,
					vector1->y + vector2->y,
					vector1->z + vector2->z
				);
}

vec3 *vec3_subc(vec3 *vector1, vec3 *vector2)
{
	return vec3_create(
					vector1->x - vector2->x,
					vector1->y - vector2->y,
					vector1->z - vector2->z
				);
}

vec3 *vec3_cross(vec3 *vec1, vec3 *vec2)
{
	vec3 *vec = vec3_create(
		vec1->y * vec2->z - vec1->z * vec2->y,
		vec1->z * vec2->x - vec1->x * vec2->z,
		vec1->x * vec2->y - vec1->y * vec2->x
		);

	vec3_destroy(vec1);
	vec3_destroy(vec2);

	return vec;
}

vec3 *vec3_crossc(vec3 *vec1, vec3 *vec2)
{
	return vec3_create(
		vec1->y * vec2->z - vec1->z * vec2->y,
		vec1->z * vec2->x - vec1->x * vec2->z,
		vec1->x * vec2->y - vec1->y * vec2->x
		);
}

float vec3_dot(vec3 *vector1, vec3 *vector2)
{
	float result = 0.0;

	for (int i = 0; i < 3; i++)
	{
		result += vector1->val[i] * vector2->val[i];
	}

	return result;
}

vec3 *vec3_norm(vec3 *vector)
{
	float magnitude = sqrt(vector->x * vector->x + vector->y * vector->y + vector->z * vector->z);
	vec3 *result = vec3_create(
						vector->x / magnitude,
						vector->y / magnitude,
						vector->z / magnitude
					);
	vec3_destroy(vector);
	return result;
}

vec3 *vec3_normc(vec3 *vector)
{
	float magnitude = sqrt(vector->x * vector->x + vector->y * vector->y + vector->z * vector->z);
	return vec3_create(
						vector->x / magnitude,
						vector->y / magnitude,
						vector->z / magnitude
					);
}