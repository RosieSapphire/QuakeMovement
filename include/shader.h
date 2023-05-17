#ifndef FBG_SHADER_H
#define FBG_SHADER_H

unsigned int shader_load(const char *vpath, const char *fpath);
void shader_uniform_mat4(unsigned int program, const char *name, float v[4][4]);
void shader_uniform_vec3(unsigned int program, const char *name, float v[3]);
void shader_uniform_int(unsigned int program, const char *name, int v);

#endif
