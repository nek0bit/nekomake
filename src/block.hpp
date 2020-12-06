#pragma once

#include <iostream>
#include <array>
#include <vector>

#include "constants.hpp"
#include "game_object.hpp"

typedef std::array<bool, 6> cubeFaces_t;

struct Block: public GameObject
{
    Block(int x = 0, int y = 0, int z = 0);

    //void render(Shader& shader, Textures& textures) override;
    
    void setX(int x);
    void setY(int y);
    void setZ(int z);

    void updateFaces(cubeFaces_t faces);
    
    int x;
    int y;
    int z;
private:
    cubeFaces_t blockFaces;
};
