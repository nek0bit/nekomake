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
    for (std::unique_ptr<Chunk>& chunk: loadedChunks)
    {
        bool chunkFound = true;
        
        switch(chunk->ready)
        {
        case CHUNK_VOXELS_NOT_GENERATED:
            for (unsigned int i = 0; i < 2; ++i )
                chunk->generateSplit();
            chunkFound = true;
            break;
        case CHUNK_FACES_NOT_UPDATED:
            chunk->updateBlockFaces();
            chunkFound = true;
            break;
        case CHUNK_MESH_NOT_GENERATED:
            chunk->generateChunkMesh();
            chunkFound = true;
            break;
        case CHUNK_READY:
        default:
            chunkFound = false;
            break;
        };
        
        if (chunkFound) break;
    }
}

void ChunkGroup::render(Shader& shader, Textures& textures)
{
    for (std::unique_ptr<Chunk>& chunk: loadedChunks)
    {
        // Let's draw the chunk now
        chunk->render(shader, textures);
    }
}
