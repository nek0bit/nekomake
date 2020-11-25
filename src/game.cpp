#include "game.hpp"


Game::Game(GLFWwindow* window, int& viewWidth, int& viewHeight) : window{ window }, viewWidth{ viewWidth }, viewHeight{ viewHeight },
running{ true }, shader{}, textures{}, VBO{ 0 }, inputs{ window, {GLFW_KEY_ESCAPE, GLFW_KEY_W, GLFW_KEY_A, GLFW_KEY_S, GLFW_KEY_D, GLFW_KEY_SPACE, GLFW_KEY_LEFT_SHIFT} },
camera{ viewWidth, viewHeight }, sample{ &VBO }, sampleObj{ &sample, 0.0, 0.0, 3.0, 45, 45, 45 }
{
	glGenBuffers(1, &VBO);

	// Directory info
	const std::string root = "../../../"; // tmp
	const std::string root_data = root + "data/";

	std::vector<std::string> textures_str = {
		root_data + "sample.jpg"
	};

	textures.load(textures_str);

	sample.init(std::vector<float>{
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		});

	shader.load(root+"shaders/vert.glsl", root+"shaders/frag.glsl");


	inputs.hideCursor();
}

Game::~Game()
{}

void Game::initGL()
{
	glEnable(GL_DEPTH_TEST);
}

void Game::update(Timer timer)
{

	inputs.update();
	inputs.updateMouse();

	if (inputs.focused)
	{
		inputs.setCursorPosition(viewWidth / 2, viewHeight / 2);
	}

	inputs.updateMouse();

	constexpr double amount = 0.01;
	constexpr float speed = 0.01f;
	camera.rotateYaw((inputs.mouse_x_last - inputs.mouse_x) * amount * timer.deltaTime);
	camera.rotatePitch(((inputs.mouse_y_last - inputs.mouse_y) * amount * timer.deltaTime) * -1);

	// Close if escape pressed
	if (inputs.keyState[KEY_ESCAPE])
	{
		glfwSetWindowShouldClose(window, true);
	}

	constexpr glm::vec3 noY{ 1.0f, 0.0f, 1.0f };

	if (inputs.keyState[KEY_W])
	{
		camera.eye += (camera.center * noY) * speed * timer.deltaTime;
	}

	if (inputs.keyState[KEY_S])
	{
		camera.eye -= (camera.center * noY) * speed * timer.deltaTime;
	}

	if (inputs.keyState[KEY_A])
	{
		camera.eye -= glm::normalize(glm::cross(camera.center, camera.up)) * speed * timer.deltaTime;
	}

	if (inputs.keyState[KEY_D])
	{
		camera.eye += (glm::cross(camera.center, camera.up)) * speed * timer.deltaTime;
	}


	// Update camera
	camera.update();
	camera.set(shader);
}

void Game::render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader.use();
	// Begin

	glBindTexture(GL_TEXTURE_2D, textures.ids[0]);
	sampleObj.render(shader);

	// End
	glfwSwapBuffers(window);
	glfwPollEvents();
}