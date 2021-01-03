#include "chunk_generator.hpp"

ChunkGenerator::ChunkGenerator(int seed) : seed{seed}
{}

ChunkGenerator::~ChunkGenerator(){}

BlockArgs ChunkGenerator::generateBlockAt(int x, int y, int z)
{
    return BlockArgs{0};
}
