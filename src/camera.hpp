#pragma once
#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.hpp"

struct Camera {
	Camera(int& viewWidth, int& viewHeight);
	~Camera();

	void set(Shader& shader);
	void update();

	// Generic functions
	void rotateYaw(float amount);
	void rotatePitch(float amount);
	void rotateRoll(float amount);

	int& viewWidth, & viewHeight;

	// Matrix
	glm::mat4 projection{ 1.0f };
	glm::mat4 view{ 1.0f };

	// Vectors
	glm::vec3 eye, center, up;

	float yaw;
	float pitch;
	float roll; // I'll set this up later
};