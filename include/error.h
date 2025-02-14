#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>

typedef enum
{
	ERR_SUCCESS = 0,
	ERR_MEM_FAIL,
	ERR_WINDOW_CREATE,
	ERR_GLAD_LOAD,
	ERR_VSHADER_COMPILE,
	ERR_FSHADER_COMPILE,
	ERR_SHADER_LINK,
	ERR_FILE_OPEN
} ERROR_TYPE;

#define ASSERT(condition, error_code)			 	\
		do 											\
		{  											\
			if (!(condition))						\
			{										\
				fprintf(stderr, "%d", error_code);	\
				exit(error_code);					\
			}										\
		} while(0)

#endif