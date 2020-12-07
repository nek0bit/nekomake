#pragma once

#include <iostream>
#include <vector>
#include <exception>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.hpp"
#include "mesh.hpp"
#include "textures.hpp"

class MeshNullptr : public std::exception
{
	virtual const char* what() const throw()
	{
		return "Mesh was nullptr, cannot be nullptr";
	}
};

struct GameObject {
	GameObject(Mesh* mesh, double x = 0.0, double y = 0.0, double z = 0.0,
               double rotX = 0.0, double rotY = 0.0, double rotZ = 0.0,
               double scaleX = 1.0, double scaleY = 1.0, double scaleZ = 1.0);
	virtual ~GameObject();

	virtual void render(Shader& shader, Textures& textures);

	glm::vec3 pos;
	glm::vec3 rot;
    glm::vec3 scale;

	Mesh* mesh;
};
