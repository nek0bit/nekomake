#include "game.hpp"

Game::Game(GLFWwindow *window, int &viewWidth, int &viewHeight) : window{ window }, viewWidth{ viewWidth }, viewHeight{ viewHeight },
running{ true }
{
	std::cout << "Window at: " << window << std::endl;
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

}