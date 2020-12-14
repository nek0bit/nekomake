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
    Block(int id, int offset_x = 0, int offset_z = 0, int x = 0, int y = 0, int z = 0);
    virtual ~Block();

    void generateMesh(std::vector<Vertex>& vertices,
                      std::vector<unsigned int>& ebo,
                      unsigned int& eboIndex,
                      TextureGrid& blockGrid);
    
    bool operator<(const Block& b) const;
    bool operator>(const Block& b) const;

    bool compare(int com_x, int com_y, int com_z) const;

    faces_t faces;

    int x, y, z, offset_x, offset_z;
    BlockInfo* info;
private:
    
    inline std::vector<unsigned int> vecAddNum(int to_add, std::vector<unsigned int> vec);
};

