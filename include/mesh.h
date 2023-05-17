#ifndef MESH_H
#define MESH_H

#include "camera.h"

struct vertex {
	float pos[3];
	float uv[2];
	float norm[3];
	float col[3];
};

struct mesh {
	int num_verts, num_indis;
	struct vertex *verts;
	unsigned int *indis;
	unsigned int vao, vbo, ebo;
	float pos[3], rot[3];
};

enum mesh_type {
	MESH_CUBE = 0,
	MESH_QUAD,
	MESH_TYPE_COUNT
};

struct mesh *mesh_create_data(struct vertex *verts, GLuint *indis,
		int num_verts, int num_indis);
struct mesh *mesh_create_file(const char *path);
struct mesh *mesh_create_type(enum mesh_type type);
void mesh_get_model_mat4(struct mesh m, float out[4][4]);
void mesh_draw(struct mesh *m, GLuint shader, GLuint texture);
void mesh_destroy(struct mesh *m);

#endif
