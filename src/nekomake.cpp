#include "nekomake.hpp"

int viewWidth = 800;
int viewHeight = 600;

Game* gamePtr = nullptr;

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	viewWidth = width;
	viewHeight = height;
	glViewport(0, 0, width, height);
	if (gamePtr != nullptr)
		gamePtr->camera.updatePerspective();
}

void error(const std::string message)
{
	std::cout << "[Error] " << message << std::endl;
}

int main()
{
	constexpr int FPS = 120;

	// Setup GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(viewWidth, viewHeight, "NekoMake", NULL, NULL);
	
	if (window == NULL)
	{
		error("Error: Failed to create GLFW window");
		glfwTerminate();
		return -1;
	}
	else
	{
		glfwMakeContextCurrent(window);
	}

	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		error("Error: Failed to initialize GLAD");
		return -3;
	}


	Timer timer = FPS;
	Game game{window, viewWidth, viewHeight};
	
	// Store a pointer to the game for the resize callback function
	gamePtr = &game;

	// Set view size
	framebufferSizeCallback(window, viewWidth, viewHeight);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	game.initGL();

	while (!glfwWindowShouldClose(window))
	{
		timer.setCurrentTime(glfwGetTime() * 1000);
		game.update(timer);
		game.render();
		std::this_thread::sleep_for(std::chrono::milliseconds(timer.getSleepTime(glfwGetTime() * 1000)));
	}

	return 0;
}
