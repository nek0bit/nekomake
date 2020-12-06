#pragma once

#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.hpp"
#include "textures.hpp"


struct Mesh {
	Mesh(unsigned int* VBO);
	~Mesh();

	void init(std::vector<float> vertices, std::vector<int> texture_ids);
	void render(Shader& shader,
                Textures& textures,
                glm::vec3& transformVertex,
                glm::vec3& rotateVertex,
                glm::vec3& scaleVertex,
                std::vector<bool> toggle_triangles = {});
private:
    int amount;
    std::vector<int> texture_ids;
	unsigned int* VBO;

	unsigned int VAO;
};

typedef std::vector<Mesh> meshGroup_t;
