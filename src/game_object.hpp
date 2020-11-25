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

class MeshNullptr : public std::exception
{
	virtual const char* what() const throw()
	{
		return "Mesh was nullptr, cannot be nullptr";
	}
};

struct GameObject {
	GameObject(Mesh* mesh, double x = 0.0, double y = 0.0, double z = 0.0,
		double rotX = 1.0, double rotY = 1.0, double rotZ = 1.0);
	~GameObject();

	void render(Shader& shader);

	glm::vec3 pos;
	glm::vec3 rot;
	float rotAmount;

	Mesh* mesh;
};