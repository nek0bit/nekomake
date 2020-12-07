#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "constants.hpp"
#include "shader.hpp"
#include "textures.hpp"
#include "mesh.hpp"
#include "camera.hpp"
#include "timer.hpp"
#include "inputs.hpp"
#include "game_object.hpp"
#include "play.hpp"

struct Game {
	Game(GLFWwindow* window, Timer& timer, int& viewWidth, int& viewHeight);
	~Game();

	void initGL();

	void update();
	void render();

	bool running;
	Camera camera;
private:
	GLFWwindow* window;
	Shader shader;
	Textures textures;
	unsigned int VBO;
	Inputs inputs;

    // Game
    std::unique_ptr<Play> play;

    meshGroup_t meshGroup;
	
	int& viewWidth;
	int& viewHeight;
};
