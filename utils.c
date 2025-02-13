#include "utils.h"

long read_line(FILE *file, char *buf)
{
	long read = 0;
	char ch;
	while (1)
	{
		fread(&ch, sizeof(char), 1, file);
		if (ch == '\n' || feof(file))
		{
			break;
		}
		buf[read] = ch;
		read++;
	}
	buf[read] = '\0';
	return (read == 0 && feof(file)) ? -1 : read;
}