#include "basic_generator.hpp"

BasicGenerator::BasicGenerator(int seed) : ChunkGenerator{seed}
{}

BlockArgs BasicGenerator::generateBlockAt(int x, int y, int z) const
{
    return BlockArgs{false, 0};
}
