#ifndef CAMERA_H
#define CAMERA_H

#include "input.h"

struct camera {
	float pos[3];
	float yaw, pitch;
};

void camera_get_look_pos(struct camera c, float out[3]);
void camera_get_front_vec(struct camera c, float out[3]);
void camera_get_side_vec(struct camera c, float out[3]);
void camera_get_view_mat4(struct camera c, float out[4][4]);
void camera_update_rotation(struct camera *c, struct input i, float sens);
void camera_get_wish_dir(struct camera c, struct input i, float wish_dir[3]);
void camera_update_position(struct camera *c, struct input i, float dt);

#endif
