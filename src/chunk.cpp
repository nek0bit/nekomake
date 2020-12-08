#include "chunk.hpp"

Chunk::Chunk() : ready{false}, chunk{}, chunkMesh{}, chunkObj{&chunkMesh, 0, 0, 0, 0, 0, 0, 1.0, 1.0, 1.0}, vertices{}, textures{},
                 ebo{}, eboIndex{0}, pos{0.0, 0.0, 0.0}, rot{0.0, 0.0, 0.0}, scale{1.0, 1.0, 1.0}, splitsGenerated{0}
{
    // Setup chunk mesh
    chunkMesh.init(vertices, textures, ebo);
    for (int i = 0; i <= constants::chunk::splitCount; ++i)
    {
            generateSplit();

    }

    updateBlockFaces();
    generateChunkMesh();
}

Chunk::~Chunk()
{
}

Block* Chunk::blockAt(unsigned int x, unsigned int y, unsigned int z) const
{
    int ySplit = static_cast<float>(y)/yHeight;
    int yWithin = y % yHeight;
    
    return chunk[ySplit][yWithin][z][x].get();
}

bool Chunk::isBlockAt(int x, int y, int z) const
{
    if (x < 0 || y < 0 || z < 0 || x > constants::chunk::volume[0]-1 || y > constants::chunk::volume[1]-1 || z > constants::chunk::volume[2]-1) return false;
    return blockAt(x, y, z) != nullptr;
}

void Chunk::updateBlockFaces()
{
    for (auto& split: chunk)
    {
        for (auto& array_block_y: split)
        {
            for (auto& array_block_z: array_block_y)
            {
                for (auto& block: array_block_z)
                {
                    std::array<bool, 6> sides = {
                        !isBlockAt(block->x-1, block->y, block->z),
                        !isBlockAt(block->x, block->y, block->z-1),
                        !isBlockAt(block->x+1, block->y, block->z),
                        !isBlockAt(block->x, block->y, block->z+1),
                        !isBlockAt(block->x, block->y+1, block->z),
                        !isBlockAt(block->x, block->y-1, block->z)
                        };

                    block->faces = sides;
                }
            }
        }
    }
}

void Chunk::generateChunkMesh()
{
    for (auto& split: chunk)
    {
        for (auto& array_block_y: split)
        {
            for (auto& array_block_z: array_block_y)
            {
                for (auto& block: array_block_z)
                {
                    block->generateMesh(vertices, textures, ebo, eboIndex);
                }
            }
        }
    }
    chunkMesh.bindBuffer(vertices, ebo);
    chunkMesh.texture_ids = textures;
}

void Chunk::generateSplit()
{
    if (!ready)
    {
        int i = 0;

        for (int x = 0; x < constants::chunk::volume[0]; ++x)
        {
            for (int y = 0; y < yHeight; ++y)
            {
                for (int z = 0; z < constants::chunk::volume[2]; ++z)
                {
                    chunk[splitsGenerated][y][z][x] = std::unique_ptr<Block>(
                        new Block(x,
                                  y+(splitsGenerated*yHeight),
                                  z));
                    i++;
                }
            }
        }
        
        if(++splitsGenerated > constants::chunk::splitCount-1) {
            ready = true;
        }
    }
}

void Chunk::update()
{
}

void Chunk::render(Shader& shader, Textures& textures)
{
    chunkObj.render(shader, textures);
}
