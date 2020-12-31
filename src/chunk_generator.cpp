#include "chunk_generator.hpp"

ChunkGenerator::ChunkGenerator(int seed) : seed{seed}
{}

ChunkGenerator::~ChunkGenerator(){}

BlockArgs ChunkGenerator::generateBlockAt(int x, int y, int z) const
{
    return BlockArgs{0};
}
