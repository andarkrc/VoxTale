#ifndef UTILS_H
#define UTILS_H

#define true 1

#define false 0

typedef struct {
	float r;
	float g;
	float b;
	float a;
} color_t;

color_t color_create(float r, float g, float b, float a);

typedef union {
	float f;
	void *p;
} voidfloat;

#endif
