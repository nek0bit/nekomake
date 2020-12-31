#pragma once

#include <iostream>
#include <array>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "transition.hpp"
#include "vertex.hpp"
#include "generic.hpp"
#include "constants.hpp"
#include "block.hpp"
#include "texture_grid.hpp"
#include "chunk_mesh_generator.hpp"
#include "chunk_generator.hpp"

enum chunk_ready
{
    CHUNK_VOXELS_NOT_GENERATED,
    CHUNK_FACES_NOT_UPDATED,
    CHUNK_MESH_NOT_GENERATED,
    CHUNK_ANIMATION_DONE,
    CHUNK_READY
};

// x, y, then z
typedef std::vector<std::shared_ptr<Block>> Voxel_t;

struct Chunk
{
    Chunk(int x, int y, int z, ChunkGenerator* chunkGenerator);
    ~Chunk();

    void update();
    void render(Shader& shader, Textures& textures);

    Block* blockAt(unsigned int x, unsigned int y, unsigned int z);
    bool isBlockAt(int x, int y, int z);
    void updateBlockAt(int x, int y, int z,
                       std::array<unsigned short int, 6> faces);

    void generateChunkMesh();
    void updateBlockFaces(bool updateBorderedChunks = false);
    void generateChunk();
    void communicateBorders();

    int state;

    // Position of chunk
    // Chunks are 3d
    int x, y, z;

    std::array<Chunk*, 6> borderedChunks;
private:
    Voxel_t chunk;
    ChunkGenerator* chunkGen;

    TextureGrid blockGrid;

    bool animationDoneLock;

    Transition chunkAnim;
    // Chunk mesh
    Mesh chunkMesh;
    GameObject chunkObj;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> ebo;
    unsigned int eboIndex;

    glm::vec3 pos;
    glm::vec3 rot;
    glm::vec3 scale;

    unsigned int splitsGenerated;
};
