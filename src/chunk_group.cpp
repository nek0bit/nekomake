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
            generateChunkAt(i, j);
        }
    }
}

ChunkGroup::~ChunkGroup()
{

}

void ChunkGroup::generateChunkAt(int x, int z)
{
    // Insert chunk
    loadedChunks.push_back(std::unique_ptr<Chunk>(new Chunk(x, z)));
    auto pos = loadedChunks.end()-1;

    // Set 
    (*pos)->borderedChunks = {getChunkAt(x-1, z),  // Behind of
                              getChunkAt(x+1, z),  // Front of
                              getChunkAt(x, z-1),  // Left of
                              getChunkAt(x, z+1)}; // Right of
}

// TODO store items in properly indexed vector so we can easily get the index without searching the chunks
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
    const int chunkUpdatePerFrame = 3;
    const int chunkGenerateSplitAmount = 2;

    // State
    int frameUpdates = 0;
    
    // Update chunk state
    for (std::unique_ptr<Chunk>& chunk: loadedChunks)
    {
        switch(chunk->state)
        {
        case CHUNK_VOXELS_NOT_GENERATED: // Load the chunk
            for (unsigned int i = 0; i < chunkGenerateSplitAmount; ++i )
                chunk->generateSplit();
            frameUpdates++;
            break;
        case CHUNK_FACES_NOT_UPDATED: // Update faces for chunk blocks
            chunk->communicateBorders(); // Make sure chunks know borders
            chunk->updateBlockFaces(true);
            frameUpdates++;
            break;
        case CHUNK_MESH_NOT_GENERATED: // Generate/Re-generate mesh for chunk
            std::cout << "Not ready..." << std::endl;
            chunk->generateChunkMesh();
            frameUpdates++;
            break;
        case CHUNK_ANIMATION_DONE:
            chunk->state = CHUNK_READY;
            break;
        case CHUNK_READY:
        default:
            chunk->update();
            break;
        };

        if (frameUpdates > chunkUpdatePerFrame)
        {
            frameUpdates = 0;
            //break;
        }

        /*if (frameUpdates == 0)
        {
            
            std::cout << "===================" << std::endl;
            std::cout << "Chunk at " << chunk->x << " and " << chunk->z << " is " << chunk.get() << std::endl;
            for (auto& i: chunk->borderedChunks)
            {
                std::cout << "0: " << i << std::endl;
            }
            }*/
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
