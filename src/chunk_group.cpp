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

Chunk* ChunkGroup::getChunkAt(int x, int z)
{
    auto it = std::find_if(loadedChunks.begin(),
                 loadedChunks.end(), [&](std::unique_ptr<Chunk>& ch) -> bool {
                                         return ch->x == x && ch->z == z;
                                     });

    if (it != loadedChunks.end())
    {
        return it->get();
    }
    return nullptr;
}

void ChunkGroup::update()
{
    // Prefs
    const int chunkUpdatePerFrame = 5;
    const int chunkGenerateSplitAmount = 2;

    // State
    int frameUpdates = 0;
    
    // Update chunk state
    for (std::unique_ptr<Chunk>& chunk: loadedChunks)
    {
        switch(chunk->ready)
        {
        case CHUNK_VOXELS_NOT_GENERATED: // Load the chunk
            for (unsigned int i = 0; i < chunkGenerateSplitAmount; ++i )
                chunk->generateSplit();
            frameUpdates++;
            break;
        case CHUNK_FACES_NOT_UPDATED: // Update faces for chunk blocks
            chunk->updateBlockFaces();
            frameUpdates++;
            break;
        case CHUNK_MESH_NOT_GENERATED: // Generate/Re-generate mesh for chunk
            chunk->generateChunkMesh();
            frameUpdates++;
            break;
        case CHUNK_READY:
        default:
            chunk->update();
            break;
        };


        if (frameUpdates > chunkUpdatePerFrame)
        {
            frameUpdates = 0;
            break;
        }
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
