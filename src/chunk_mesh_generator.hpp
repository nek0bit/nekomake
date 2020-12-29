#pragma once

#include <vector>

#include "constants.hpp"
#include "vertex.hpp"
#include "block.hpp"

struct ChunkOffset
{
    int x;
    int y;
    int z;
};

struct ChunkMeshGenerator
{
    ChunkMeshGenerator() = default;

    void generateMesh(Block& block,
                      ChunkOffset chunk_offsets,
                      std::vector<Vertex>& vertices,
                      std::vector<unsigned int>& ebo,
                      unsigned int& eboIndex,
                      TextureGrid& blockGrid);
private:
    std::vector<unsigned int> vecAddNum(int to_add, std::vector<unsigned int> vec);
};
