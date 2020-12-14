#include "chunk_group.hpp"

ChunkGroup::ChunkGroup()
    : loadedChunks{}
{
    const int x = 10; 
    const int z = 10;

    // Generate chunks
    for (unsigned int i = 0; i < x; ++i)
    {
        for (unsigned int j = 0; j < z; ++j)
        {
            loadedChunks.push_back(std::unique_ptr<Chunk>(new Chunk(i, j)));
        }
    }
}

ChunkGroup::~ChunkGroup()
{

}

void ChunkGroup::update()
{

}

void ChunkGroup::render(Shader& shader, Textures& textures)
{
    for (std::unique_ptr<Chunk>& chunk: loadedChunks)
    {
        // Let's draw the chunk now
        chunk->render(shader, textures);
    }
}
