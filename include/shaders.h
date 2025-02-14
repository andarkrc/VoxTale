#ifndef SHADERS_H
#define SHADERS_H

#include <stdio.h>
#include <stdlib.h>

unsigned int shader_get_default(void);

unsigned int shader_load(char *vertex_file, char *fragment_file);

void shader_set_mat4(unsigned int shader, char *uniform, float **mat);

void shader_set_target(unsigned int shader);
void shader_reset_target(void);

#endif