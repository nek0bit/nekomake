#pragma once

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct Inputs {
	Inputs(GLFWwindow* window, std::vector<int> keyCodes);
	~Inputs();

	void update();
	void updateMouse();
	void setCursorPosition(double x, double y);
	void hideCursor();
	void showCursor();

	double mouse_x;
	double mouse_y;
	double mouse_x_last;
	double mouse_y_last;

	bool focused;

	std::vector<int> keyCodes;
	std::vector<bool> keyState;
private:
	GLFWwindow* window;
};