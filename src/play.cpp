#include "play.hpp"

Play::Play()
{

}

Play::~Play()
{

}

void Play::update(Timer& timer,
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
    constexpr float rotateSpeed = 100;
    constexpr float moveSpeed = 0.01;

    double move_x = (inputs.mouse_x_last - inputs.mouse_x) * amount,
        move_y = (inputs.mouse_y_last - inputs.mouse_y) * amount * -1;

    // Rotate camera
    camera.yaw += move_x * rotateSpeed;
    camera.pitch += move_y * rotateSpeed;

    // Clamp values and reverse
    camera.pitch = generic::clamp(camera.pitch, -89.9, 89.9);

    if (camera.yaw > 360)
        camera.yaw = camera.yaw - 360;
    else if (camera.yaw < 0)
        camera.yaw = camera.yaw + 360;


    // Handle movement
    if (inputs.keyState[KEY_W])
	{
        camera.eye += moveSpeed * camera.center * timer.deltaTime;
	}

    if (inputs.keyState[KEY_S])
    {
        camera.eye -= moveSpeed * camera.center * timer.deltaTime;
    }
    
	// Update camera
	camera.update();
	camera.set(shader);

    inputs.hideCursor();
}

void Play::render()
{
    
}
