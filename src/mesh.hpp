#pragma once

#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.hpp"

struct Mesh {
	Mesh(unsigned int* VBO);
	~Mesh();

	void init(std::vector<float> vertices);
	void render(Shader& shader, glm::vec3& transformVertex, glm::vec3& rotateVertex);

	std::vector<float> vertices;
	unsigned int* VBO;

	unsigned int VAO;
private:
	int count;
};
