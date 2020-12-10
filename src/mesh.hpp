#pragma once

#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "vertex.hpp"
#include "shader.hpp"
#include "textures.hpp"


struct Mesh {
	Mesh();
	~Mesh();

	void init(std::vector<Vertex> vertices,
              std::vector<unsigned int> texture_ids,
              std::vector<unsigned int> indices = {});
    
	void render(Shader& shader,
                Textures& textures,
                glm::vec3& transformVertex,
                glm::vec3& rotateVertex,
                glm::vec3& scaleVertex);

    void bindBuffer(std::vector<Vertex>& vertices, std::vector<unsigned int> indices = {});
    
    std::vector<unsigned int> texture_ids;
private:
    std::vector<unsigned int> indices;
    int amount;
	unsigned int VBO;
    unsigned int EBO;
	unsigned int VAO;
};

typedef std::vector<Mesh> meshGroup_t;
