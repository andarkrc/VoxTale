#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include "shaders.h"
#include "error.h"

static unsigned int default_shader;

unsigned int shader_get_default(void)
{
	static char compiled = 0;

	if (!compiled)
	{
		const char *const vertex_code = 
		"#version 460 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

		const char *const fragment_code = 
		"#version 460 core"
		"out vec4 FragColor;"
		"void main()\n"
		"{\n"
		"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";

		int compile_status;
		unsigned int vertex_shader;
		vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex_shader, 1, &vertex_code, NULL);
		glCompileShader(vertex_shader);
		glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &compile_status);
		ASSERT(compile_status, ERR_VSHADER_COMPILE);

		unsigned int fragment_shader;
		fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_shader, 1, &fragment_code, NULL);
		glCompileShader(fragment_shader);
		glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &compile_status);
		ASSERT(compile_status, ERR_FSHADER_COMPILE);

		unsigned int shader_program;
		shader_program = glCreateProgram();
		glAttachShader(shader_program, vertex_shader);
		glAttachShader(shader_program, fragment_shader);
		glLinkProgram(shader_program);

		int link_status;
		glGetProgramiv(shader_program, GL_LINK_STATUS, &link_status);
		ASSERT(link_status, ERR_SHADER_LINK);

		default_shader = shader_program;
		compiled = 1;
	}

	return default_shader;
}

unsigned int shader_load(char *vertex_file, char *fragment_file)
{
	FILE *vfile = fopen(vertex_file, "rt");
	FILE *ffile = fopen(fragment_file, "rt");
	ASSERT(vfile && ffile, ERR_FILE_OPEN);

	size_t vfile_size, ffile_size;
	fseek(vfile, 0, SEEK_END);
	fseek(ffile, 0, SEEK_END);
	vfile_size = ftell(vfile);
	ffile_size = ftell(ffile);
	fseek(vfile, 0, SEEK_SET);
	fseek(ffile, 0, SEEK_SET);

	char *vertex_code = malloc(vfile_size + 1);
	char *fragment_code = malloc(ffile_size + 1);
	ASSERT(vertex_code && fragment_code, ERR_MEM_FAIL);

	fread(vertex_code, sizeof(char), vfile_size, vfile);
	fread(fragment_code, sizeof(char), ffile_size, ffile);

	vertex_code[vfile_size] = '\0';
	fragment_code[ffile_size] = '\0';

	int compile_status;
	unsigned int vertex_shader;
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, (const char * const *)&vertex_code, NULL);
	glCompileShader(vertex_shader);
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &compile_status);
	ASSERT(compile_status, ERR_VSHADER_COMPILE);

	unsigned int fragment_shader;
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1,  (const char * const *)&fragment_code, NULL);
	glCompileShader(fragment_shader);
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &compile_status);
	ASSERT(compile_status, ERR_FSHADER_COMPILE);

	unsigned int shader_program;
	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);

	int link_status;
	glGetProgramiv(shader_program, GL_LINK_STATUS, &link_status);
	ASSERT(link_status, ERR_SHADER_LINK);

	free(fragment_code);
	free(vertex_code);
	fclose(vfile);
	fclose(ffile);

	return shader_program;
}