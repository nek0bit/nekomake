#pragma once

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "constants.hpp"
#include "shader.hpp"
#include "textures.hpp"
#include "mesh.hpp"
#include "camera.hpp"
#include "timer.hpp"
#include "inputs.hpp"
#include "game_object.hpp"

struct Play {
    Play();
    ~Play();

    void update(Timer& timer,
                Shader& shader,
                Camera& camera,
                Inputs& inputs,
                Textures& textures,
                unsigned int VBO,
                int& viewWidth,
                int& viewHeight);
    void render();
};
