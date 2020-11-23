#pragma once

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct Inputs {
	Inputs(GLFWwindow* window);
	~Inputs();

private:
	GLFWwindow* window;
};