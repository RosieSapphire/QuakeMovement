#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>

struct input {
	float mouse_last[2];
	float mouse_delta[2];
	uint8_t a_held : 1;
	uint8_t d_held : 1;
	uint8_t w_held : 1;
	uint8_t s_held : 1;
	uint8_t shift_held : 1;
	uint8_t pad : 3;
	GLFWwindow *win_ptr;
};

struct input input_init(GLFWwindow *win);
struct input input_update(struct input i);

#endif
