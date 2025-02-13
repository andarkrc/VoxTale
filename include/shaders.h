#ifndef SHADERS_H
#define SHADERS_H

#include <stdio.h>
#include <stdlib.h>

unsigned int shader_get_default(void);

unsigned int shader_load(char *vertex_file, char *fragment_file);

#endif