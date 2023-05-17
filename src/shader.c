#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <glad/gl.h>
#include "shader.h"

static GLuint shader_compile(const char *path, int type)
{
	GLuint shader = glCreateShader(type);

	FILE *file = fopen(path, "r");
	size_t file_size = 0L;
	char *source = NULL;

	fseek(file, 0, SEEK_END);
	file_size = ftell(file);
	rewind(file);
	source = malloc(file_size);
	fread(source, sizeof(char), file_size, file);
	fclose(file);
	source[--file_size] = 0;

	GLint status;

	glShaderSource(shader, 1, (const char **)&source, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if(status)
		return shader;

	char log[512];

	glGetShaderInfoLog(shader, 512, NULL, log);
	printf("Failed to create shader from '%s': %s\n", path, log);
	free(source);

	return 0;
}

unsigned int shader_load(const char *vpath, const char *fpath)
{
	GLuint vert_shader = shader_compile(vpath, GL_VERTEX_SHADER);
	GLuint frag_shader = shader_compile(fpath, GL_FRAGMENT_SHADER);
	GLuint program = glCreateProgram();

	glAttachShader(program, vert_shader);
	glAttachShader(program, frag_shader);
	glLinkProgram(program);

	glDeleteShader(vert_shader);
	glDeleteShader(frag_shader);

	return program;
}

static int shader_get_loc(unsigned int program, const char *name)
{
	int loc = glGetUniformLocation(program, name);

	if(loc == -1) {
		fprintf(stderr, "Failed to find uniform '%s' in shader %d\n",
				name, program);
		exit(EXIT_FAILURE);
	}

	return loc;
}

void shader_uniform_mat4(unsigned int program, const char *name, float v[4][4])
{
	int loc = shader_get_loc(program, name);
	glUniformMatrix4fv(loc, 1, GL_FALSE, (float *)v);
}

void shader_uniform_vec3(unsigned int program, const char *name, float v[3])
{
	int loc = shader_get_loc(program, name);
	glUniform3fv(loc, 1, v);
}

void shader_uniform_int(unsigned int program, const char *name, int v)
{
	int loc = shader_get_loc(program, name);
	glUniform1i(loc, v);
}
