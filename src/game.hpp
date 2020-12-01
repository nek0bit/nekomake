#pragma once

#include <iostream>
#include <vector>
#include <array>
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
#include "editor.hpp"

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

    // Game
    Editor editor;

    std::vector<Mesh> meshGroup;
	
	int& viewWidth;
	int& viewHeight;
};
