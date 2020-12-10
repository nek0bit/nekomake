#include "game.hpp"


Game::Game(GLFWwindow* window,
           Timer& timer,
           int& viewWidth,
           int& viewHeight) : window{ window }, viewWidth{ viewWidth }, viewHeight{ viewHeight },
                              running{ true }, shader{}, textures{},
                              inputs{ window, {
        GLFW_KEY_ESCAPE, GLFW_KEY_W, GLFW_KEY_A, GLFW_KEY_S,
        GLFW_KEY_D, GLFW_KEY_R, GLFW_KEY_SPACE, GLFW_KEY_LEFT_SHIFT} },
                              play{nullptr},
                              camera{ viewWidth, viewHeight }
{
	// Directory info
    const std::string root = DATA; // tmp
    const std::string root_data = root + "data/";


    std::vector<std::string> textures_str = {
        root_data + "sample.png",
        root_data + "dirt.png"
    };

    textures.load(textures_str);

    /*
      BLOCK FOR REFERENCE
      ===================
      meshGroup.push_back(Mesh{});

      meshGroup[MESH_BLOCK].init(std::vector<float>{
            -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, // 0
            1.0f, -1.0f, -1.0f, 1.0f, 0.0f, // 1
            1.0f, 1.0f, -1.0f, 1.0f, 1.0f, // 2
            -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, // 3

            -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, // 4
            1.0f, -1.0f, 1.0f, 1.0f, 0.0f, // 5
            1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // 6
            -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, // 7

            -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // 8
            -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, // 9
            -1.0f, -1.0f, -1.0f, 0.0f, 1.0f, // 10
            -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, // 11

            1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // 12
            1.0f, -1.0f, -1.0f, 0.0f, 1.0f, // 13
            1.0f, -1.0f, 1.0f, 0.0f, 0.0f, // 14

            1.0f, -1.0f, -1.0f, 1.0f, 1.0f, // 15
            1.0f, -1.0f, 1.0f, 1.0f, 0.0f, // 16

            -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // 17
            
            
            
        }, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {
            0, 1, 2, 2, 3, 0,
            4, 5, 6, 6, 7, 4,
            8, 9, 10, 10, 11, 8,
            12, 2, 13, 13, 14, 12,
            10, 15, 16, 16, 4, 10,
            3, 2, 12, 12, 17, 3
        }
        );
    */

    constants::block::blockMesh = &meshGroup[MESH_BLOCK];

    shader.load(root+"shaders/vert.glsl", root+"shaders/frag.glsl");

    play = std::unique_ptr<Play>{new Play(timer, shader, camera, textures, meshGroup)};
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

    play->update(inputs);
}

void Game::render()
{
	glClearColor(119.0/255.0, 181.0/255.0, 229.0/255.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader.use();
	// Begin

    play->render();

	// End
	glfwSwapBuffers(window);
	glfwPollEvents();
}
