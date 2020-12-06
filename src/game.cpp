#include "game.hpp"


Game::Game(GLFWwindow* window,
           Timer& timer,
           int& viewWidth,
           int& viewHeight) : window{ window }, viewWidth{ viewWidth }, viewHeight{ viewHeight },
                              running{ true }, shader{}, textures{}, VBO{ 0 },
                              inputs{ window, {
        GLFW_KEY_ESCAPE, GLFW_KEY_W, GLFW_KEY_A, GLFW_KEY_S,
        GLFW_KEY_D, GLFW_KEY_R, GLFW_KEY_SPACE, GLFW_KEY_LEFT_SHIFT} },
                              play{},
                              camera{ viewWidth, viewHeight }
{
    glGenBuffers(1, &VBO);

	// Directory info
    const std::string root = DATA; // tmp
    const std::string root_data = root + "data/";


    std::vector<std::string> textures_str = {
        root_data + "dirt.png"
    };

    textures.load(textures_str);

    meshGroup.push_back(Mesh{&VBO});

    meshGroup[MESH_BLOCK].init(std::vector<float>{
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
        }, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});

    constants::blockMesh = &meshGroup[MESH_BLOCK];

    shader.load(root+"shaders/vert.glsl", root+"shaders/frag.glsl");
    
    play.setAll(timer, shader, camera, textures, VBO, meshGroup);
}

Game::~Game()
{}

void Game::initGL()
{
    glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    
}

void Game::update()
{
    // Close if escape pressed
	if(inputs.keyState[KEY_ESCAPE])
	{
		glfwSetWindowShouldClose(window, true);
	}

    play.update(inputs);
}

void Game::render()
{
	glClearColor(119.0/255.0, 181.0/255.0, 229.0/255.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader.use();
	// Begin

    play.render();

	// End
	glfwSwapBuffers(window);
	glfwPollEvents();
}
