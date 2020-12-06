#include "play.hpp"

Play::Play() : timer{nullptr}, shader{nullptr}, camera{nullptr},
               textures{nullptr}, VBO{nullptr}, meshGroup{nullptr}
{

}

Play::~Play()
{}

void Play::setAll(Timer& timer,
                  Shader& shader,
                  Camera& camera,
                  Textures& textures,
                  unsigned int& VBO,
                  meshGroup_t& meshGroup)
{
    setTimer(timer);
    setShader(shader);
    setCamera(camera);
    setTextures(textures);
    setVBO(VBO);
    setMeshGroup(meshGroup);
}

void Play::setTimer(Timer& timer) { this->timer = &timer; }
void Play::setShader(Shader& shader) { this->shader = &shader; }
void Play::setCamera(Camera& camera) { this->camera = &camera; }
void Play::setTextures(Textures& textures) { this->textures = &textures; }
void Play::setVBO(unsigned int& VBO) { this->VBO = &VBO; }
void Play::setMeshGroup(meshGroup_t& meshGroup) { this->meshGroup = &meshGroup; }

bool Play::nullptrCheck()
{
    return !(timer && shader && camera && textures && VBO && meshGroup);
}

void Play::handleCamera(Inputs& inputs)
{
    // Update mouse
    inputs.update();
    inputs.updateMouse();

    if(inputs.focused)
    {
        inputs.setCursorPosition(camera->viewWidth / 2, camera->viewHeight / 2);
    }

    inputs.updateMouse();

    constexpr double amount = 0.001;
    constexpr float rotateSpeed = 100;
    constexpr float moveSpeed = 0.01;

    double move_x = (inputs.mouse_x_last - inputs.mouse_x) * amount,
        move_y = (inputs.mouse_y_last - inputs.mouse_y) * amount * -1;

    // Rotate camera
    camera->yaw += move_x * rotateSpeed;
    camera->pitch += move_y * rotateSpeed;

    // Clamp camera
    camera->pitch = generic::clamp(camera->pitch, -89.9, 89.9);

    if(camera->yaw > 360)
        camera->yaw = camera->yaw - 360;
    else if(camera->yaw < 0)
        camera->yaw = camera->yaw + 360;


    // Handle movement
    if(inputs.keyState[KEY_W])
	{
        camera->eye += moveSpeed * camera->center * timer->deltaTime;
	}

    if(inputs.keyState[KEY_S])
    {
        camera->eye -= moveSpeed * camera->center * timer->deltaTime;
    }
    
	// Update camera
	camera->update();
	camera->set(*shader);

    inputs.hideCursor();
}

void Play::update(Inputs& inputs)
{   
    handleCamera(inputs);
}

void Play::render()
{
    GameObject temp{&(*meshGroup)[MESH_BLOCK],
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f};
    GameObject tempa{&(*meshGroup)[MESH_BLOCK],
        1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f};
    temp.toggles = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1};
    temp.render(*shader, *textures);
    tempa.render(*shader, *textures);

    
}
