#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <array>
#include <algorithm>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct Shader {
	Shader(const std::string vertShaderFilename, const std::string fragShaderFilename);
	~Shader();

	void use();
	unsigned int getUniform(const std::string uniform);
	void setUniformMatrix4fv(unsigned int location, const GLfloat* value);

	unsigned int program;
};