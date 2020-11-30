#include "editor.hpp"

Editor::Editor()
{

}

Editor::~Editor()
{

}

void Editor::update(Timer& timer,
                    Shader& shader,
                    Camera& camera,
                    Inputs& inputs,
                    Textures& textures,
                    unsigned int VBO,
                    int& viewWidth,
                    int& viewHeight)
{
    if (inputs.keyState[KEY_R])
    {
        camera.eye.x = 0;
        camera.eye.y = 0;
        camera.eye.z = 0;
    }
    // Update mouse
    inputs.update();
    inputs.updateMouse();

    if (inputs.focused)
    {
        inputs.setCursorPosition(viewWidth / 2, viewHeight / 2);
    }

    inputs.updateMouse();

    constexpr double amount = 0.001;
    constexpr float speed = 0.001;

    std::cout << camera.eye.x << " " << camera.eye.y << " " << camera.eye.z << std::endl;

    double move_x = (inputs.mouse_x_last - inputs.mouse_x) * amount * timer.deltaTime,
        move_y = (inputs.mouse_y_last - inputs.mouse_y) * amount * timer.deltaTime * -1;

    //camera.eye += move_x * speed * timer.deltaTime;
    //camera.eye += move_y * speed * timer.deltaTime;

    camera.eye.x += move_y;
    camera.eye.y = 3;
    camera.eye.z += move_x;

    
    camera.pitch = -30;

	// Update camera
	camera.update();
	camera.set(shader);

    inputs.hideCursor();
}

void Editor::render()
{
    std::cout << "Render called" << std::endl;
}
