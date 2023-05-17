#include <math.h>
#include <string.h>
#include "util.h"

float clampf(float x, float min, float max)
{
	return fmaxf(fminf(x, max), min);
}

void vec3_copy(float src[3], float dst[3])
{
	bcopy(src, dst, sizeof(float) * 3);
}

void vec3_one(float v[3])
{
	vec3_copy((float[3]){1, 1, 1}, v);
}

void vec3_zero(float v[3])
{
	bzero(v, sizeof(float) * 3);
}

void vec3_add(float v1[3], float v2[3], float vo[3])
{
	for(int i = 0; i < 3; i++)
		vo[i] = v1[i] + v2[i];
}

void vec3_sub(float v1[3], float v2[3], float vo[3])
{
	for(int i = 0; i < 3; i++)
		vo[i] = v1[i] - v2[i];
}

float vec3_dot(float v1[3], float v2[3])
{
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

float vec3_magnitude(float v[3])
{
	return sqrtf(vec3_dot(v, v));
}

void vec3_scale(float v[3], float s)
{
	for(int i = 0; i < 3; i++)
		v[i] *= s;
}

void vec3_normalize(float v[3])
{
	float mag = vec3_magnitude(v);

	if(!mag)
		return;

	vec3_scale(v, 1.0f / mag);
}

void vec3_cross(float v1[3], float v2[3], float vo[3])
{
	vo[0] = v1[1] * v2[2] - v1[2] * v2[1];
	vo[1] = v1[2] * v2[0] - v1[0] * v2[2];
	vo[2] = v1[0] * v2[1] - v1[1] * v2[0];
}

void mat4_zero(float out[4][4])
{
	bzero(out, sizeof(float) * 16);
}

void mat4_identity(float out[4][4])
{
	mat4_zero(out);

	for(int i = 0; i < 4; i++)
		out[i][i] = 1;
}

void mat4_multiplty(float m1[4][4], float m2[4][4], float mo[4][4])
{
	float m1_tmp[4][4];
	bcopy(m1, m1_tmp, sizeof(m1_tmp));
	mat4_zero(mo);

	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			for(int k = 0; k < 4; k++) {
				mo[j][i] += m1_tmp[k][i] * m2[j][k];
			}
		}
	}
}

void mat4_rotate(float out[4][4], float axis[3], float angle_rad)
{
	float rot[4][4];
	const float angle_sin = sinf(angle_rad);
	const float angle_cos = cosf(angle_rad);

	mat4_zero(rot);
	rot[0][0] = angle_cos + (axis[0] * axis[0]) * (1 - angle_cos);
	rot[1][0] = axis[0] * axis[1] * (1 - angle_cos) - axis[2] * angle_sin;
	rot[2][0] = axis[0] * axis[2] * (1 - angle_cos) + axis[1] * angle_sin;

	rot[0][1] = axis[1] * axis[0] * (1 - angle_cos) + axis[2] * angle_sin;
	rot[1][1] = angle_cos + (axis[1] * axis[1]) * (1 - angle_cos);
	rot[2][1] = axis[1] * axis[2] * (1 - angle_cos) - axis[0] * angle_sin;

	rot[0][2] = axis[2] * axis[0] * (1 - angle_cos) - axis[1] * angle_sin;
	rot[1][2] = axis[2] * axis[1] * (1 - angle_cos) + axis[0] * angle_sin;
	rot[2][2] = angle_cos + (axis[2] * axis[2]) * (1 - angle_cos);

	rot[3][3] = 1.0f;

	mat4_multiplty(out, rot, out);
}

void mat4_translate(float out[4][4], float move[3])
{
	vec3_add(out[3], move, out[3]);
}

void mat4_lookat(float eye[3], float focus[3], float up[3], float out[4][4])
{
	float f[3];
	vec3_sub(focus, eye, f);

	vec3_normalize(f);

	float s[3];
	vec3_cross(up, f, s);
	vec3_normalize(s);

	float u[3];
	vec3_cross(f, s, u);

	out[0][0] = s[0];
	out[0][1] = u[0];
	out[0][2] = f[0];
	out[0][3] = 0.0f;
                 
	out[1][0] = s[1];
	out[1][1] = u[1];
	out[1][2] = f[1];
	out[1][3] = 0.0f;
                 
	out[2][0] = s[2];
	out[2][1] = u[2];
	out[2][2] = f[2];
	out[2][3] = 0.0f;

	out[3][0] = -vec3_dot(s, eye);
	out[3][1] = -vec3_dot(u, eye);
	out[3][2] = -vec3_dot(f, eye);
	out[3][3] = 1.0f;
}

void mat4_perspective(float fov_deg, float aspect,
		float near, float far, float out[4][4])
{
	float fov_itan = 1.0f / tanf(fov_deg * DEG_TO_RAD * 0.5f);
	float z_range = 1.0f / (near - far);

	mat4_zero(out);
	out[0][0] = fov_itan / aspect;
	out[1][1] = fov_itan;
	out[2][2] = (near + far) * z_range;
	out[2][3] = -1.0f;
	out[3][2] = 2.0f * near * far * z_range;
}
