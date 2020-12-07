#pragma once

#include <iostream>
#include <array>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "generic.hpp"
#include "constants.hpp"
#include "block.hpp"

constexpr int yHeight = (constants::chunk::volume[1]/constants::chunk::splitCount);
// 4D array [split, y, z, x]
typedef std::array<
    std::array<
        std::array<
            std::array<
                std::unique_ptr<Block>,
                constants::chunk::volume[0]>,
            constants::chunk::volume[2]>,
        constants::chunk::volume[1]/constants::chunk::splitCount>,
    constants::chunk::splitCount> Voxel_t;

struct Chunk
{
    Chunk(unsigned int* VBO);
    ~Chunk();

    void update();
    void render(Shader& shader, Textures& textures);

    Block* blockAt(unsigned int x, unsigned int y, unsigned int z) const;
    bool isBlockAt(int x, int y, int z) const;

    void generateChunkMesh();
    void updateBlockFaces();
    void generateSplit();
private:
    bool ready;
    // a 1dim array should be fine here
    Voxel_t chunk;

    // Chunk mesh
    Mesh chunkMesh;
    std::vector<float> vertices;
    std::vector<int> textures;

    glm::vec3 pos;
    glm::vec3 rot;
    glm::vec3 scale;

    unsigned int splitsGenerated;
};
