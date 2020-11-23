#include "nekomake.hpp"

int viewWidth = 800;
int viewHeight = 600;

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	viewWidth = width;
	viewHeight = height;
	glViewport(0, 0, width, height);
}

void error(const std::string message)
{
	std::cout << "[Error] " << message << std::endl;
}

int main()
{
	constexpr int FPS = 120;
	constexpr int frameDel = 1000 / FPS;

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

	// Set view size
	framebufferSizeCallback(window, viewWidth, viewHeight);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	Timer timer = 120;
	Game game{window, viewWidth, viewHeight};

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
