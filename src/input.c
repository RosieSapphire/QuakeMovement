#include <string.h>
#include <GLFW/glfw3.h>
#include "input.h"
#include "util.h"

struct input input_init(GLFWwindow *win)
{
	struct input i;
	bzero(&i, sizeof(i));
	i.win_ptr = win;
	return i;
}

struct input input_update(struct input i)
{
	i.a_held = glfwGetKey(i.win_ptr, GLFW_KEY_A);
	i.d_held = glfwGetKey(i.win_ptr, GLFW_KEY_D);
	i.w_held = glfwGetKey(i.win_ptr, GLFW_KEY_W);
	i.s_held = glfwGetKey(i.win_ptr, GLFW_KEY_S);
	i.shift_held = glfwGetKey(i.win_ptr, GLFW_KEY_LEFT_SHIFT);

	double m[2];
	glfwGetCursorPos(i.win_ptr, m, m + 1);
	i.mouse_delta[0] = m[0] - i.mouse_last[0];
	i.mouse_delta[1] = m[1] - i.mouse_last[1];
	i.mouse_last[0] = m[0];
	i.mouse_last[1] = m[1];

	return i;
}
