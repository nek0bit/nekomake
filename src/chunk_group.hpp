#pragma once

#include <vector>
#include <memory>
#include <algorithm>

#include "shader.hpp"
#include "textures.hpp"
#include "chunk.hpp"


struct ChunkGroup
{
    ChunkGroup();
    ~ChunkGroup();

    void update();
    void render(Shader& shader, Textures& textures);

    std::vector<std::unique_ptr<Chunk>> loadedChunks;
private:
    Chunk* getChunkAt(int x, int y, int z);
    void generateChunkAt(int x, int y, int z);
};
