#ifndef MATRIX_H
#define MATRIX_H

#include <math.h>

typedef struct
{
	float data[16];
	float *val[4];
} mat4;

typedef union
{
	float val[3];
	struct 
	{
		float x;
		float y;
		float z;
	};
} vec3;

typedef union 
{
	float val[4];
	struct 
	{
		float x;
		float y;
		float z;
		float w;
	};
} vec4;

mat4 *mat4_create(void);
vec4 *vec4_create(float x, float y, float z, float w);
vec3 *vec3_create(float x, float y, float z);

vec4 *vec4_from_vec3(vec3 *vec);
vec3 *vec3_from_vec4(vec4 *vec);

void mat4_destroy(mat4 *mat);
void vec4_destroy(vec4 *vec);
void vec3_destroy(vec3 *vec);

mat4 *mat4_identity(void);
mat4 *mat4_null(void);

mat4 *mat4_dup(mat4 *matrix);

mat4 *mat4_add(mat4 *matrix1, mat4 *matrix2);
mat4 *mat4_sub(mat4 *matrix1, mat4 *matrix2);
mat4 *mat4_mul(mat4 *matrix1, mat4 *matrix2);

mat4 *mat4_smul(mat4 *matrix, float scalar);
float mat4_det(mat4 *m);

mat4 *mat4_addc(mat4 *matrix1, mat4 *matrix2);
mat4 *mat4_subc(mat4 *matrix1, mat4 *matrix2);
mat4 *mat4_mulc(mat4 *matrix1, mat4 *matrix2);

mat4 *mat4_rotatexr(float angle);
mat4 *mat4_rotateyr(float angle);
mat4 *mat4_rotatezr(float angle);
mat4 *mat4_rotatexd(float angle);
mat4 *mat4_rotateyd(float angle);
mat4 *mat4_rotatezd(float angle);

mat4 *mat4_translate(float x, float y, float z);
mat4 *mat4_scale(float x, float y, float z);

mat4 *mat4_update_rotatexr(mat4 *mat, float angle);
mat4 *mat4_update_rotateyr(mat4 *mat, float angle);
mat4 *mat4_update_rotatezr(mat4 *mat, float angle);
mat4 *mat4_update_rotatexd(mat4 *mat, float angle);
mat4 *mat4_update_rotateyd(mat4 *mat, float angle);
mat4 *mat4_update_rotatezd(mat4 *mat, float angle);

mat4 *mat4_update_translate(mat4 *mat, float x, float y, float z);
mat4 *mat4_update_scale(mat4 *mat, float x, float y, float z);

mat4 *mat4_transpose(mat4 *matrix);

mat4 *mat4_ortho(float left, float right, float bottom, float top, float znear, float zfar);
mat4 *mat4_perspectiver(float fovy, float aspect, float znear, float zfar);
mat4 *mat4_perspectived(float fovy, float aspect, float znear, float zfar);
mat4 *mat4_lookat(vec3 *pos, vec3 *target, vec3 *up);
mat4 *mat4_lookatc(vec3 *pos, vec3 *target, vec3 *up);

vec4 *vec4_matmulc(mat4 *matrix, vec4 *vector);
vec4 *vec4_matmul(mat4 *matrix, vec4 *vector);

vec4 *vec4_add(vec4 *vector1, vec4 *vector2);
vec4 *vec4_sub(vec4 *vector1, vec4 *vector2);

vec4 *vec4_addc(vec4 *vector1, vec4 *vector2);
vec4 *vec4_subc(vec4 *vector1, vec4 *vector2);

float vec4_dot(vec4 *vector1, vec4 *vector2);
vec4 *vec4_crossxyz(vec4 *vec1, vec4 *vec2);
vec4 *vec4_crossxyzc(vec4 *vec1, vec4 *vec2);

vec3 *vec3_add(vec3 *vector1, vec3 *vector2);
vec3 *vec3_sub(vec3 *vector1, vec3 *vector2);

vec3 *vec3_addc(vec3 *vector1, vec3 *vector2);
vec3 *vec3_subc(vec3 *vector1, vec3 *vector2);

float vec3_dot(vec3 *vector1, vec3 *vector2);
vec3 *vec3_cross(vec3 *vec1, vec3 *vec2);
vec3 *vec3_crossc(vec3 *vec1, vec3 *vec2);

vec3 *vec3_norm(vec3 *vector);
vec3 *vec3_normc(vec3 *vector);

#endif