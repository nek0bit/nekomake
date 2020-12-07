#pragma once

#include <iostream>
#include <array>
#include <vector>

#include "constants.hpp"
#include "game_object.hpp"

typedef std::array<bool, 6> faces_t;

struct Block
{
    Block(int x = 0, int y = 0, int z = 0);
    virtual ~Block();

    void generateMesh(std::vector<float>& vertices, std::vector<int>& textures);
    
    bool operator<(const Block& b) const;
    bool operator>(const Block& b) const;

    bool compare(int com_x, int com_y, int com_z) const;

    faces_t faces;
    
    int x;
    int y;
    int z;
};

