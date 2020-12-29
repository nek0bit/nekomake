#pragma once

#include <iostream>
#include <array>
#include <memory>
#include <vector>

#include "blockinfo.hpp"
#include "vertex.hpp"
#include "constants.hpp"
#include "game_object.hpp"
#include "texture_grid.hpp"

typedef std::array<bool, 6> faces_t;

struct Block
{
    Block(int id, int x = 0, int y = 0, int z = 0);
    virtual ~Block();
    
    bool operator<(const Block& b) const;
    bool operator>(const Block& b) const;

    faces_t faces;

    int x, y, z;
    BlockInfo* info;
};

