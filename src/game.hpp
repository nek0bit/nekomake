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
#include "mesh.hpp"
#include "camera.hpp"
#include "timer.hpp"


struct Game {
	Game(GLFWwindow* window, int& viewWidth, int& viewHeight);
	~Game();

	void initGL();

	void update(Timer timer);
	void render();

	bool running;
private:
	GLFWwindow* window;
	Shader shader;
	Textures textures;
	Camera camera;
	unsigned int VBO;

	Mesh sample;
	
	int& viewWidth;
	int& viewHeight;
};