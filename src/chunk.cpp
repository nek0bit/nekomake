#include "chunk.hpp"

Chunk::Chunk(int x, int z)
    : ready{false},
      chunk{},
      blockGrid{constants::block::pixelSize, constants::block::pixelSize,
                constants::block::texWidth, constants::block::texHeight},
      x{x},
      z{z},
      chunkMesh{},
      chunkObj{&chunkMesh, 0, 0, 0, 0, 0, 0, 1.0, 1.0, 1.0},
      vertices{},
      ebo{},
      eboIndex{0},
      pos{0.0, 0.0, 0.0},
      rot{0.0, 0.0, 0.0},
      scale{1.0, 1.0, 1.0},
      splitsGenerated{0}
{
    // Setup chunk mesh
    chunkMesh.init(vertices, ebo);
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

Block* Chunk::blockAt(unsigned int x, unsigned int y, unsigned int z)
{
    int ySplit = static_cast<float>(y)/yHeight;
    int yWithin = y % yHeight;

    try
    {
        return &chunk.at(ySplit).at(x + (yWithin*yHeight) + (z*constants::chunk::volume[0]*yHeight));
    }
    catch(std::out_of_range& err)
    {
        return nullptr;
    }
}

bool Chunk::isBlockAt(int x, int y, int z)
{
    if (x >= 0 && y >= 0 && z >= 0 &&
        x < constants::chunk::volume[0] &&
        y < constants::chunk::volume[1] &&
        z < constants::chunk::volume[2])
    {
        return blockAt(x, y, z);
    }
    return false;
}

void Chunk::updateBlockFaces()
{
    for (auto& split: chunk)
    {
        for (auto& block: split)
        {
            const int bx = block.x;
            const int by = block.y;
            const int bz = block.z;
            
            std::array<bool, 6> sides = {
                !isBlockAt(bx, by, bz-1), // Left side
                !isBlockAt(bx, by, bz+1), // Right side
                !isBlockAt(bx-1, by, bz), // Front side
                !isBlockAt(bx+1, by, bz), // Back side
                !isBlockAt(bx, by-1, bz), // Bottom side
                !isBlockAt(bx, by+1, bz)  // Top side
            };
            
            block.faces = sides;
        }
    }
}

void Chunk::generateChunkMesh()
{
    for (auto& split: chunk)
    {
        for (auto& block: split)
        {
            block.generateMesh(vertices, ebo, eboIndex, blockGrid);
        }
    }
    chunkMesh.bindBuffer(vertices, ebo);
}

void Chunk::generateSplit()
{
    if (!ready)
    {
        for (int z = 0; z < constants::chunk::volume[2]; ++z)
        {
            for (int y = 0; y < yHeight; ++y)
            {
                for (int x = 0; x < constants::chunk::volume[0]; ++x)
                {
                    chunk[splitsGenerated].push_back(Block{0,
                                                           this->x*constants::chunk::volume[0],
                                                           this->z*constants::chunk::volume[2],
                                                           x,
                                                           y+(splitsGenerated*yHeight),
                                                           z});
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
    if (!ready)
    {
        
    }
}

void Chunk::render(Shader& shader, Textures& textures)
{
    chunkObj.render(shader, textures);
}
