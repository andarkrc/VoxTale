#include <stdio.h>
#include <stdlib.h>
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <time.h>

#include "utils.h"
#include "error.h"
#include "matrix.h"
#include "data_structures.h"
#include "models.h"
#include "shaders.h"
#include "textures.h"
#include "voxel.h"

int window_width;
int window_height;

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	window = window;
	glViewport(0, 0, width, height);
	window_width = width;
	window_height = height;
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

	unsigned int voxel_shader = shader_load("./assets/shaders/voxelvertex.glsl",
											"./assets/shaders/voxelfragment.glsl");

	vbuffer *square = model_load_from_obj_color("./assets/models/square.obj", "square", 0.8f, 0.1f, 0.3f, 1.0f);

	texture *smile = texture_load_rgba("./assets/textures/smile.png", "smile");
	texture *empty = texture_load_rgba("./assets/textures/empty.png", "empty");

	mat4 *stand = mat4_identity();
	mat4 *move_left = mat4_translate(-0.5f, 0.0f, 0.0f);
	mat4 *rotate_right = mat4_rotatezd(-45.0f);
		
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glEnable(GL_DEPTH_TEST);
	window_width = 800;
	window_height = 600;
	
	shader_set_target(voxel_shader);

	mat4 *ortho = mat4_ortho(-400.f, 400.f, -300.f, 300.f, 0.1f, 100.f);
	//mat4 *ortho = mat4_ortho(0.f, 800.f, 0.f, 600.f, 0.1f, 100.f);
	mat4 *perspective = mat4_perspectived(45.0f, 1.0 * window_width / window_height, 0.1f, 10000.f);
	mat4 *scale = mat4_scale(10.0f, 10.0f, 10.0f);
	mat4 *rotate = mat4_rotatexd(-70.0f);

	mat4 *sq = mat4_mulc(rotate, scale);

	//mat4 *view = mat4_translate(0.f, 0.f, -200.f);
	//mat4 *view = mat4_identity();
	mat4 *view = mat4_lookat(	vec3_create(-100.0f, 100.f, 200.0f),
								vec3_create(0.0f, 0.0f, 0.0f),
								vec3_create(0.0f, 1.0f, 0.0f));

	voxel_model *voxel = voxel_get_default();
	vec3 *voxel_color[6];
	voxel_color[0] = vec3_create(0.3f, 0.8f, 0.1f);
	voxel_color[1] = vec3_create(0.545f, 0.271f, 0.075f);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		processInput(window);

		shader_set_mat4(voxel_shader, "transform", scale);
		shader_set_mat4(voxel_shader, "projection", perspective);
		shader_set_mat4(voxel_shader, "view", view);

		for (int i = 0; i < 6; i++)
		{
			if (i == 4)
			{
				shader_set_vec3(voxel_shader, "color", voxel_color[0]);
			}
			else
			{
				shader_set_vec3(voxel_shader, "color", voxel_color[1]);
			}
			glBindVertexArray(voxel->face[i]->vao);
			glDrawArrays(GL_TRIANGLES, 0, voxel->face[i]->size);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	models_destroy();
	textures_destroy();
	return ERR_SUCCESS;
}