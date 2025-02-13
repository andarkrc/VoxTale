#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>

#define true 1

#define false 0

typedef union {
	float f;
	void *p;
} voidfloat;

#define float_to_void(val) ((voidfloat)val).p
#define void_to_float(val) ((voidfloat)val).f

long read_line(FILE *file, char *buf);

#endif
