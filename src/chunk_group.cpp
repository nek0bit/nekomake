#include "chunk_group.hpp"

ChunkGroup::ChunkGroup()
    : loadedChunks{}
{
    const int xMax = 10;
    const int yMax = 10;
    const int zMax = 10;

    // Generate chunks
    for (unsigned int x = 0; x < xMax; ++x)
    {
        for (unsigned int y = 0; y < yMax; ++y)
        {
            for (unsigned int z = 0; z < zMax; ++z)
            {
                generateChunkAt(x, y, z);
            }
        }
    }
}

ChunkGroup::~ChunkGroup()
{

}

void ChunkGroup::generateChunkAt(int x, int y, int z)
{
    // Insert chunk
    loadedChunks.push_back(std::unique_ptr<Chunk>(new Chunk(x, y, z)));
    auto pos = loadedChunks.end()-1;

    // Set 
    (*pos)->borderedChunks = {getChunkAt(x-1, y, z),  // Behind of
                              getChunkAt(x+1, y, z),  // Front of
                              getChunkAt(x, y, z-1),  // Left of
                              getChunkAt(x, y, z+1)}; // Right of
}

// TODO store items in properly indexed vector so we can easily get the index without searching the chunks
Chunk* ChunkGroup::getChunkAt(int x, int y, int z)
{
    auto it = std::find_if(loadedChunks.begin(),
                 loadedChunks.end(), [&](std::unique_ptr<Chunk>& ch) -> bool {
                                         return ch->x == x && ch->y == y && ch->z == z;
                                     });

    if (it != loadedChunks.end())
    {
        return it->get();
    }
    return nullptr;
}

void ChunkGroup::update()
{
    // Update chunk state
    for (std::unique_ptr<Chunk>& chunk: loadedChunks)
    {
        switch(chunk->state)
        {
        case CHUNK_VOXELS_NOT_GENERATED: // Load the chunk
            chunk->generateChunk();
            break;
        case CHUNK_FACES_NOT_UPDATED: // Update faces for chunk blocks
            chunk->communicateBorders(); // Make sure chunks know borders
            chunk->updateBlockFaces(true);
            break;
        case CHUNK_MESH_NOT_GENERATED: // Generate/Re-generate mesh for chunk
            chunk->generateChunkMesh();
            break;
        case CHUNK_ANIMATION_DONE:
        case CHUNK_READY:
        default:
            chunk->update();
            break;
        };
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
