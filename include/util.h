#ifndef UTIL_H
#define UTIL_H

#define EPSILON 0.0001f
#define PI 3.14159f
#define PI_INV  0.3183098861838710434f

#define RAD_TO_DEG  57.29577951309678781159f
#define DEG_TO_RAD  0.01745329251993888889f

float clampf(float x, float min, float max);

void vec3_copy(float src[3], float dst[3]);
void vec3_one(float v[3]);
void vec3_zero(float v[3]);
void vec3_add(float v1[3], float v2[3], float vo[3]);
void vec3_sub(float v1[3], float v2[3], float vo[3]);
float vec3_dot(float v1[3], float v2[3]);
float vec3_magnitude(float v[3]);
void vec3_scale(float v[3], float s);
void vec3_normalize(float v[3]);
void vec3_cross(float v1[3], float v2[3], float vo[3]);

void mat4_zero(float out[4][4]);
void mat4_identity(float out[4][4]);
void mat4_multiplty(float m1[4][4], float m2[4][4], float mo[4][4]);
void mat4_rotate(float out[4][4], float axis[3], float angle_rad);
void mat4_translate(float out[4][4], float move[3]);
void mat4_lookat(float eye[3], float focus[3], float up[3], float out[4][4]);
void mat4_perspective(float fov_deg, float aspect,
		float near, float far, float out[4][4]);

#endif
