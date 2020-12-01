#include "game.hpp"


Game::Game(GLFWwindow* window,
           int& viewWidth,
           int& viewHeight) : window{ window }, viewWidth{ viewWidth }, viewHeight{ viewHeight },
                              running{ true }, shader{}, textures{}, VBO{ 0 },
                              inputs{ window, {
        GLFW_KEY_ESCAPE, GLFW_KEY_W, GLFW_KEY_A, GLFW_KEY_S,
        GLFW_KEY_D, GLFW_KEY_R, GLFW_KEY_SPACE, GLFW_KEY_LEFT_SHIFT} },
                              editor{},
                              camera{ viewWidth, viewHeight }
{
    glGenBuffers(1, &VBO);

	// Directory info
    const std::string root = DATA; // tmp
    const std::string root_data = root + "data/";

    std::vector<std::string> textures_str = {
        root_data + "cursor.png"
    };

    textures.load(textures_str);

    meshGroup.push_back(Mesh{&VBO});

    meshGroup[MESH_TEST_BLOCK].init(std::vector<float>{
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
}

Game::~Game()
{}

void Game::initGL()
{
	glEnable(GL_DEPTH_TEST);
}

void Game::update(Timer timer)
{
    // Close if escape pressed
	if (inputs.keyState[KEY_ESCAPE])
	{
		glfwSetWindowShouldClose(window, true);
	}

    editor.update(timer, shader, camera, inputs, textures, VBO, viewWidth, viewHeight);
}

void Game::render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader.use();
	// Begin

    textures.bind_texture(0);
    //editor.render();
    GameObject temp{&meshGroup[MESH_TEST_BLOCK],
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.25, 0.25, 0.25};
    temp.render(shader);

	// End
	glfwSwapBuffers(window);
	glfwPollEvents();
}
