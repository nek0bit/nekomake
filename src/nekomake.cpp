#include "nekomake.hpp"

int viewWidth = 800;
int viewHeight = 600;

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	viewWidth = width;
	viewHeight = height;
}

void error(const std::string message)
{
	std::cout << "[Error] " << message << std::endl;
}

int main()
{
	constexpr int FPS = 120;
	constexpr int frameDel = 1000 / FPS;
	const std::string dir = "../../../"; // tmp

	// Setup GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(viewWidth, viewHeight, "NekoMake", NULL, NULL);
	
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

	Game game{window, viewWidth, viewHeight};

	game.initGL();

	while (game.running)
	{

	}

	return 0;
}
