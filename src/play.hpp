#pragma once

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "generic.hpp"
#include "constants.hpp"
#include "shader.hpp"
#include "textures.hpp"
#include "mesh.hpp"
#include "camera.hpp"
#include "timer.hpp"
#include "inputs.hpp"
#include "game_object.hpp"
#include "block.hpp"
#include "chunk.hpp"
#include "chunk_group.hpp"

struct Play {
    Play(Timer& timer,
         Shader& shader,
         Camera& camera,
         Textures& textures,
         meshGroup_t& meshGroup);
    ~Play();

    void update(Inputs& inputs);
    void render();
private:
    // Store as pointer references since they are commonly used and cleans up code
    Timer& timer;
    Shader& shader;
    Camera& camera;
    Textures& textures;
    
    meshGroup_t& meshGroup;

    ChunkGroup chunkGroup;

    bool nullptrCheck(); // Just checks if no nullptrs for the above pointer references

    void handleCamera(Inputs& inputs);
};
