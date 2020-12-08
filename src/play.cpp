#include "play.hpp"

Play::Play(Timer& timer,
         Shader& shader,
         Camera& camera,
         Textures& textures,
         meshGroup_t& meshGroup) : timer{timer}, shader{shader}, camera{camera},
                                   textures{textures}, meshGroup{meshGroup}, test{}
{
    
}

Play::~Play()
{}

void Play::handleCamera(Inputs& inputs)
{
    // Update mouse
    inputs.update();
    inputs.updateMouse();

    if(inputs.focused)
    {
        inputs.setCursorPosition(camera.viewWidth / 2, camera.viewHeight / 2);
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

    // Clamp camera
    camera.pitch = generic::clamp(static_cast<double>(camera.pitch), -89.9, 89.9);

    if(camera.yaw > 360)
        camera.yaw = camera.yaw - 360;
    else if(camera.yaw < 0)
        camera.yaw = camera.yaw + 360;


    // Handle movement
    if(inputs.keyState[KEY_W])
	{
        camera.eye += moveSpeed * camera.center * timer.deltaTime;
	}

    if(inputs.keyState[KEY_S])
    {
        camera.eye -= moveSpeed * camera.center * timer.deltaTime;
    }
    
	// Update camera
	camera.update();
	camera.set(shader);

    inputs.hideCursor();
}

void Play::update(Inputs& inputs)
{   
    handleCamera(inputs);
}

void Play::render()
{
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    //Block block{0, 0, 0};
    //block.updateFaces({0, 1, 1, 1, 1, 1});
    //block.render(*shader, *textures);

    test.render(shader, textures);
    
}
