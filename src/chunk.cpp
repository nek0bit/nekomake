#include "chunk.hpp"

Chunk::Chunk(int x, int y, int z, ChunkGenerator* chunkGenerator)
    : state{0},
      x{x},
      y{y},
      z{z},
      borderedChunks{},
      chunk{},
      chunkGen{chunkGenerator},
      blockGrid{constants::block::pixelSize, constants::block::pixelSize,
                constants::block::texWidth, constants::block::texHeight},
      animationDoneLock{false},
      chunkAnim{-30, 0.20},
      chunkMesh{},
      chunkObj{&chunkMesh, 0, -30, 0, 0, 0, 0, 1.0, 1.0, 1.0},
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
}

Chunk::~Chunk()
{
}

Block* Chunk::blockAt(unsigned int x, unsigned int y, unsigned int z)
{
    constexpr int xVol = constants::chunk::volume[0];
    constexpr int yVol = constants::chunk::volume[1];
    constexpr int zVol = constants::chunk::volume[2];

    // 3d to 1d array (since 1d arrays are faster I believe)
    return chunk.at(yVol*xVol*z + yVol * y + x).get();
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
    // We can have access to chunk borders
    // X
    else if (x == -1 && borderedChunks[0] != nullptr)
    {
        return borderedChunks[0]->blockAt(z, y, constants::chunk::volume[0]-1);
    }
    else if (x == constants::chunk::volume[0] && borderedChunks[1] != nullptr)
    {
        return borderedChunks[1]->blockAt(z, y, 0);
    }
    // Y
    else if (y == -1 && borderedChunks[4] != nullptr)
    {
        return borderedChunks[4]->blockAt(z, constants::chunk::volume[1]-1, x);
    }
    else if (y == constants::chunk::volume[1] && borderedChunks[5] != nullptr)
    {
        return borderedChunks[5]->blockAt(z, 0, x);
    }
    // Z
    else if (z == -1 && borderedChunks[2] != nullptr)
    {
        return borderedChunks[2]->blockAt(0, y, constants::chunk::volume[2]-1);
    }
    else if (z == constants::chunk::volume[2] && borderedChunks[3] != nullptr)
    {
        return borderedChunks[3]->blockAt(0, y, x);
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

// Link chunks together
void Chunk::communicateBorders()
{
    for (size_t i = 0; i < borderedChunks.size(); ++i)
    {
        if (borderedChunks[i] == nullptr) continue;

        unsigned short ind = 0;
        switch(i)
        {
        case 0: ind = 1; break;
        case 1: ind = 0; break;
        case 2: ind = 3; break;
        case 3: ind = 2; break;
        case 4: ind = 5; break;
        case 5: ind = 4; break;
        default: break;
        };

        borderedChunks[i]->borderedChunks[ind] = this;
        borderedChunks[i]->updateBlockFaces(true);
    }
}

// Should only be used once per chunk generation
void Chunk::updateBlockFaces(bool updateBorderedChunks)
{
    
    for (auto& block: chunk)
    {
        if (block == nullptr)
        {
            continue;
        }
            
        const int bx = block->x;
        const int by = block->y;
        const int bz = block->z;
                        
        block->faces = {
            !isBlockAt(bx, by, bz-1), // Left side
            !isBlockAt(bx, by, bz+1), // Right side
            !isBlockAt(bx-1, by, bz), // Front side
            !isBlockAt(bx+1, by, bz), // Back side
            !isBlockAt(bx, by-1, bz), // Bottom side
            !isBlockAt(bx, by+1, bz)  // Top side
        };
    }
    
    state = CHUNK_MESH_NOT_GENERATED;
}

void Chunk::generateChunkMesh()
{
    ChunkMeshGenerator meshGen{};
    for (auto& block: chunk)
    {
        if (block == nullptr)
        {
            continue;
        }

        meshGen.generateMesh(*block.get(), {x, y, z}, vertices, ebo, eboIndex, blockGrid);
    }
    
    chunkMesh.bindBuffer(vertices, ebo);

    // Chunk is ready!
    state = CHUNK_READY;
    chunkAnim.value = 0;
}

void Chunk::generateChunk()
{
    for (int z = 0; z < constants::chunk::volume[2]; ++z)
    {
        for (int y = 0; y < constants::chunk::volume[1]; ++y)
        {
            for (int x = 0; x < constants::chunk::volume[0]; ++x)
            {
                // Adjusts the coordinates by the current chunk coordinates
                const int realX = x+(this->x*constants::chunk::volume[0]);
                const int realY = y+(this->y*constants::chunk::volume[1]);
                const int realZ = z+(this->z*constants::chunk::volume[2]);

                // Returns the properties for the block, such as if there even is a block
                BlockArgs props = chunkGen->generateBlockAt(realX, realY, realZ);

                if (props.emptyBlock)
                {
                    chunk.push_back(nullptr);
                }
                else
                {
                    chunk.push_back(std::make_shared<Block>(Block{props.id, x, y, z}));
                }
            }
        }
    }
        
    state = CHUNK_FACES_NOT_UPDATED;
}

void Chunk::update()
{
    if (!animationDoneLock)
    {
        chunkAnim.update();
        chunkObj.pos.y = chunkAnim.get();

        // Small efficiency to stop calculating animating early
        if (chunkAnim.get() > -0.02)
        {
            animationDoneLock = true; // Dont animate anymore
            chunkObj.pos.y = 0;
            state = CHUNK_ANIMATION_DONE;
        }
    }
}

void Chunk::render(Shader& shader, Textures& textures)
{
    chunkObj.render(shader, textures);
}
