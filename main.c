#include <stdio.h>
#include <stdlib.h>
#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include "utils.h"
#include "error.h"
#include "matrix.h"
#include "data_structures.h"

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
		
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	
		processInput(window);
	
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return ERR_SUCCESS;
}