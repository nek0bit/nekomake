#pragma once

#include <iostream>
#include <array>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "vertex.hpp"
#include "generic.hpp"
#include "constants.hpp"
#include "block.hpp"
#include "texture_grid.hpp"

constexpr int yHeight = (constants::chunk::volume[1]/constants::chunk::splitCount);

enum chunk_ready
{
    CHUNK_VOXELS_NOT_GENERATED,
    CHUNK_FACES_NOT_UPDATED,
    CHUNK_MESH_NOT_GENERATED,
    CHUNK_READY
};

// x, y, then z
typedef std::array<std::vector<Block>, constants::chunk::splitCount> Voxel_t;

struct Chunk
{
    Chunk(int x, int z);
    ~Chunk();

    void update();
    void render(Shader& shader, Textures& textures);

    Block* blockAt(unsigned int x, unsigned int y, unsigned int z);
    bool isBlockAt(int x, int y, int z);

    void generateChunkMesh();
    void updateBlockFaces();
    void generateSplit();

    int ready;
private:
    // a 1dim array should be fine here
    Voxel_t chunk;

    TextureGrid blockGrid;

    // Position of chunk
    int x, z;

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
