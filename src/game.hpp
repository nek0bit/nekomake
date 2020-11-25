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
#include "inputs.hpp"
#include "game_object.hpp"

enum keys
{
	KEY_ESCAPE = 0,
	KEY_W,
	KEY_A,
	KEY_S,
	KEY_D,
	KEY_SPACE,
	KEY_LEFT_SHIFT
};

struct Game {
	Game(GLFWwindow* window, int& viewWidth, int& viewHeight);
	~Game();

	void initGL();

	void update(Timer timer);
	void render();

	bool running;
	Camera camera;
private:
	GLFWwindow* window;
	Shader shader;
	Textures textures;
	unsigned int VBO;
	Inputs inputs;

	Mesh sample;
	GameObject sampleObj;
	
	int& viewWidth;
	int& viewHeight;
};