#include "chunk.hpp"

Chunk::Chunk(int x, int z)
    : ready{0},
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
    /*for (int i = 0; i <= constants::chunk::splitCount; ++i)
    {
            generateSplit();
    }

    updateBlockFaces();
    generateChunkMesh();*/
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

// Sides
// 0 = Do not update
// 1 = Disable
// 2 = Enable
void Chunk::updateBlockAt(int x, int y, int z,
                          std::array<unsigned short int, 6> faces)
{
    Block* block = blockAt(x, y, z);
    if (block != nullptr)
    {    
        for (unsigned short int i = 0; i < 6; ++i)
        {
            switch(faces[i])
            {
            case 1:
                faces[i] = false;
                break;
            case 2:
                faces[i] = true;
            default:
                break;
            }
        }
    }
}

// Should only be used once per chunk generation
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
    ready = CHUNK_MESH_NOT_GENERATED;
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
    ready = CHUNK_READY;
}

void Chunk::generateSplit()
{
    if (ready == CHUNK_VOXELS_NOT_GENERATED)
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
            ready = CHUNK_FACES_NOT_UPDATED;
        }
    }
}

void Chunk::update()
{}

void Chunk::render(Shader& shader, Textures& textures)
{
    chunkObj.render(shader, textures);
}
