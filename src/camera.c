#include <stdio.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include "camera.h"
#include "input.h"
#include "util.h"

void camera_get_look_pos(struct camera c, float out[3])
{
	float look_pos[3] = {
		cosf(c.yaw * PI) * cosf(c.pitch * PI),
		sinf(c.pitch * PI),
		sinf(c.yaw * PI) * cosf(c.pitch * PI),
	};

	vec3_add(c.pos, look_pos, out);
}

void camera_get_front_vec(struct camera c, float out[3])
{
	float look_pos[3];
	camera_get_look_pos(c, look_pos);

	for(int i = 0; i < 3; i++)
		out[i] = look_pos[i] - c.pos[i];

	vec3_normalize(out);
}

void camera_get_side_vec(struct camera c, float out[3])
{
	float front_vec[3];
	camera_get_front_vec(c, front_vec);

	vec3_cross(front_vec, (float[3]){0, 1, 0}, out);
	vec3_normalize(out);
}

void camera_get_view_mat4(struct camera c, float out[4][4])
{
	float look_pos[3];
	camera_get_look_pos(c, look_pos);
	mat4_lookat(c.pos, look_pos, (float[3]){0, 1, 0}, out);
}

void camera_update_rotation(struct camera *c, struct input i, float sens)
{
	c->yaw += i.mouse_delta[0] * sens;
	c->pitch += i.mouse_delta[1] * sens;
	c->pitch = clampf(c->pitch, -0.5f, 0.5f);
}

void camera_get_wish_dir(struct camera c, struct input i, float wish_dir[3])
{
	float front_vec[3];
	camera_get_front_vec(c, front_vec);
	vec3_scale(front_vec, i.s_held - i.w_held);

	float side_vec[3];
	camera_get_side_vec(c, side_vec);
	vec3_scale(side_vec, i.a_held - i.d_held);

	vec3_add(front_vec, side_vec, wish_dir);
	vec3_normalize(wish_dir);
}

void camera_update_position(struct camera *c, struct input i, float dt)
{
	float wish_dir[3];
	camera_get_wish_dir(*c, i, wish_dir);
	vec3_scale(wish_dir, dt);
	vec3_add(c->pos, wish_dir, c->pos);
}
