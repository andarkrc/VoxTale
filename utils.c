#include "utils.h"

color_t color_create(float r, float g, float b, float a)
{
	color_t color;
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;

	return color;
}