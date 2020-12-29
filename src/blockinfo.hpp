#pragma once

#include <string>
#include <array>
#include <vector>

typedef std::vector<std::array<int, 2>> textureSides_t;

enum BLOCKS_ENUM
{
    BLOCK_MOON_SOIL,
    BLOCK_STONE,
};

struct BlockInfo
{    
    int id;
    std::string name;
    textureSides_t sideTextures;
};
