#pragma once

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.hpp"
#include "textures.hpp"

struct Game {
	Game(GLFWwindow *window, int &viewWidth, int &viewHeight);
	~Game();

	void initGL();

	void update();
	void render();

	bool running;
private:
	GLFWwindow *window;
	Shader shader;
	Textures textures;
	
	int &viewWidth;
	int &viewHeight;
};