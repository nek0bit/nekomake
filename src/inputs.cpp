#include "inputs.hpp"

Inputs::Inputs(GLFWwindow* window, std::vector<int> keyCodes) : mouse_x{}, mouse_y{}, mouse_x_last{},
mouse_y_last{}, focused{}, keyCodes{ keyCodes }, keyState{}, window{ window }
{
	keyState.resize(keyCodes.size());
}

Inputs::~Inputs()
{}

void Inputs::setCursorPosition(double x, double y)
{
	glfwSetCursorPos(window, x, y);
}

void Inputs::hideCursor()
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void Inputs::showCursor()
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Inputs::update()
{
	focused = static_cast<bool>(glfwGetWindowAttrib(window, GLFW_FOCUSED));

	for (size_t i = 0; i < keyCodes.size(); ++i)
	{
		keyState[i] = glfwGetKey(window, keyCodes[i]) == GLFW_PRESS;
	}

	
}

void Inputs::updateMouse()
{
	mouse_x_last = mouse_x;
	mouse_y_last = mouse_y;
	glfwGetCursorPos(window, &mouse_x, &mouse_y);
}