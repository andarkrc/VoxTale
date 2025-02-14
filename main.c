#include <stdio.h>
#include <stdlib.h>
#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include "utils.h"
#include "error.h"
#include "matrix.h"
#include "data_structures.h"
#include "models.h"
#include "shaders.h"
#include "textures.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	window = window;
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main(void)
{	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		
	GLFWwindow *window = glfwCreateWindow(800, 600, "VoxTale", NULL, NULL);
	ASSERT(window, ERR_WINDOW_CREATE);
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		fprintf(stderr, "could not load glad\n");
		return ERR_GLAD_LOAD;
	}

	unsigned int default_shader = shader_get_default();

	unsigned int s3d_shader = shader_load("./assets/shaders/simple3drendervertex.glsl",
										  "./assets/shaders/simple3drenderfragment.glsl");

	vbuffer *triangle = model_load_from_obj("./assets/models/triangle.obj", "triangle");
	vbuffer *square = model_load_from_obj_color("./assets/models/square.obj", "square", 0.8f, 0.1f, 0.3f, 1.0f);

	texture *smile = texture_load_rgba("./assets/textures/smile.png", "smile");
	texture *empty = texture_load_rgba("./assets/textures/empty.png", "empty");

	mat4 *stand = mat4_identity();
	mat4 *move_left = mat4_translate(-0.5f, 0.0f, 0.0f);
	mat4 *rotate_right = mat4_rotatezd(-45.0f);
	
		
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	shader_set_target(s3d_shader);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	
		processInput(window);

		shader_set_mat4(s3d_shader, "transform", (float **)stand->val);
		glBindTexture(GL_TEXTURE_2D, empty->id);
		glBindVertexArray(triangle->vao);
		glDrawArrays(GL_TRIANGLES, 0, triangle->size);

		shader_set_mat4(s3d_shader, "transform", (float **)move_left->val);
		glBindVertexArray(square->vao);
		glBindTexture(GL_TEXTURE_2D, smile->id);
		glDrawArrays(GL_TRIANGLES, 0, square->size);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	models_destroy();
	textures_destroy();
	return ERR_SUCCESS;
}