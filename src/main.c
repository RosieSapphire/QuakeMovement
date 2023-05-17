#include <assert.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "input.h"
#include "render_layer.h"
#include "shader.h"
#include "util.h"

#define WIDTH 1280
#define HEIGHT 720
#define ASPECT_RATIO ((float)WIDTH / (float)HEIGHT)

GLFWwindow *window_create_centered(int width, int height, const char *title);

int main(void)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = window_create_centered(WIDTH, HEIGHT,
			"Funny Block Game (Not Roblox)");

	assert(glfwRawMouseMotionSupported());

	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	gladLoadGL(glfwGetProcAddress);
	glEnable(GL_DEPTH);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	struct render_layer *layer = render_layer_create(WIDTH, HEIGHT);

	GLuint cube_shader =
		shader_load("shaders/base.vert", "shaders/base.frag");
	GLuint fbo_shader =
		shader_load("shaders/fbo.vert", "shaders/fbo.frag");

	float projection[4][4];
	mat4_perspective(70.0f, ASPECT_RATIO, 0.1f, 50, projection);

	struct camera cam = {{2, 0, 0}, 0, 0};
	struct mesh *test_mesh = mesh_create_file("models/stud.glb");

	float time_last = glfwGetTime();
	struct input input = input_init(window);

	while(!glfwWindowShouldClose(window)) {
		float time_now = glfwGetTime();
		float time_delta = time_now - time_last;

		time_last = time_now;

		camera_update_rotation(&cam, input, 0.0006f);
		camera_update_position(&cam, input, time_delta);
		test_mesh->rot[1] += time_delta;

		render_layer_bind_and_clear(layer, 0.05f, 0.1f, 0.2f, 1.0f);

		float model[4][4];
		mesh_get_model_mat4(*test_mesh, model);

		float view[4][4];
		camera_get_view_mat4(cam, view);

		glUseProgram(cube_shader);
		shader_uniform_mat4(cube_shader, "u_model", model);
		shader_uniform_mat4(cube_shader, "u_view", view);
		shader_uniform_mat4(cube_shader, "u_projection", projection);
		mesh_draw(test_mesh, cube_shader, 0);

		render_layer_draw(layer, fbo_shader, WIDTH, HEIGHT);

		glfwSwapBuffers(window);
		glfwPollEvents();

		input = input_update(input);
	}

	glDeleteProgram(fbo_shader);
	glDeleteProgram(cube_shader);
	mesh_destroy(test_mesh);
	render_layer_destroy(layer);
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

GLFWwindow *window_create_centered(int width, int height, const char *title)
{
	GLFWwindow *window = glfwCreateWindow(width, height, title,
			NULL, NULL);

	glfwMakeContextCurrent(window);

	GLFWmonitor *monitor = glfwGetPrimaryMonitor();
	int monitor_w, monitor_h;
	int window_x, window_y;

	glfwGetMonitorWorkarea(monitor, NULL, NULL, &monitor_w, &monitor_h);
	window_x = (monitor_w >> 1) - (width >> 1);
	window_y = (monitor_h >> 1) - (height >> 1);
	glfwSetWindowPos(window, window_x, window_y);

	return window;
}
