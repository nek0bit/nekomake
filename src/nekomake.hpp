#pragma once

// External
#include <iostream>
#include <thread>
#include <algorithm>
#include <vector>
#include <chrono>
#include <thread>
#include <sstream>
#include <fstream>
#include <cstring>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Internal
void error(const std::string message);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);

#include "game.hpp"
#include "timer.hpp"