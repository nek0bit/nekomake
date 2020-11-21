#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.hpp"

struct Game {
	Game(GLFWwindow *window, int &viewWidth, int &viewHeight);
	~Game();

	void initGL();

	void update();
	void render();

	bool running;
private:
	GLFWwindow *window;
	
	int &viewWidth;
	int &viewHeight;
};