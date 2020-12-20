#include "chunk.hpp"

Chunk::Chunk(int x, int z)
    : state{0},
      x{x},
      z{z},
      borderedChunks{},
      chunk{},
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

    chunk.resize(constants::chunk::splitCount);
}

Chunk::~Chunk()
{
}

Block* Chunk::blockAt(unsigned int x, unsigned int y, unsigned int z)
{
    int ySplit = static_cast<float>(y)/yHeight;
    int yWithin = y % yHeight;


    // Using a *VERY* slow but correct block finder until I fix the code below (which is much faster but something is off)
    auto search = std::find_if(chunk[ySplit].begin(), chunk[ySplit].end(), [&](std::shared_ptr<Block>& bl) -> bool {
                                                                               if (bl == nullptr) return false;
                                                                               return bl->x == x && bl->y == y && bl->z == z;
                                                                           });

    if (search != chunk[ySplit].end())
    {
        return (*search).get();
    }
    else
    {
        return nullptr;
    }

    /*
    try
    {
        return chunk[ySplit].at(x + (yWithin*yHeight) + (z*constants::chunk::volume[0]*yHeight)).get();
    }
    catch(std::out_of_range& err)
    {
        return nullptr;
    }
    */
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
        default: break;
        };

        borderedChunks[i]->borderedChunks[ind] = this;
    }
}

// Should only be used once per chunk generation
void Chunk::updateBlockFaces(bool updateBorderedChunks)
{
    
    for (auto& split: chunk)
    {
        for (auto& block: split)
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
    }
    state = CHUNK_MESH_NOT_GENERATED;
}

void Chunk::generateChunkMesh()
{
    for (auto& split: chunk)
    {
        for (auto& block: split)
        {
            if (block == nullptr)
            {
                continue;
            }
            block->generateMesh(vertices, ebo, eboIndex, blockGrid);
        }
    }
    chunkMesh.bindBuffer(vertices, ebo);
    state = CHUNK_READY;
    chunkAnim.value = 0;
}

void Chunk::generateSplit()
{
    if (state == CHUNK_VOXELS_NOT_GENERATED)
    {
        for (int x = 0; x < constants::chunk::volume[0]; ++x)
        {
            for (int y = (splitsGenerated*yHeight); y < (splitsGenerated*yHeight)+yHeight; ++y)
            {
                for (int z = 0; z < constants::chunk::volume[2]; ++z)
                {
                    if (x == 0 && y % 5 == 0 && z == 0 )
                    {
                        chunk[splitsGenerated].push_back(nullptr);
                    } else {   
                        chunk[splitsGenerated].push_back(
                            std::make_shared<Block>(Block{0,
                                                          this->x*constants::chunk::volume[0],
                                                          this->z*constants::chunk::volume[2],
                                                          x,
                                                          y,
                                                          z}));
                    }
                }
            }
        }
        
        if(++splitsGenerated > constants::chunk::splitCount-1) {
            state = CHUNK_FACES_NOT_UPDATED;
        }
    }
}

void Chunk::update()
{
    if (!animationDoneLock)
    {
        chunkAnim.update();
        chunkObj.pos.y = chunkAnim.get();
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
