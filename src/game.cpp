#include "game.hpp"

Game::Game(GLFWwindow *window, int &viewWidth, int &viewHeight) : window{ window }, viewWidth{ viewWidth }, viewHeight{ viewHeight },
running{ true }, shader{}, textures{}
{
	// Directory info
	const std::string root = "../../../"; // tmp
	const std::string root_data = root + "data/";

	std::vector<std::string> textures_str = {
		root_data + "sample.jpg"
	};

	textures.load(textures_str);

	shader.load(root+"shaders/vert.glsl", root+"shaders/frag.glsl");
}

Game::~Game()
{}

void Game::initGL()
{
	glEnable(GL_DEPTH_TEST);
}

void Game::update()
{

}

void Game::render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Begin


	// End
	glfwSwapBuffers(window);
	glfwPollEvents();
}