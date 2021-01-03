#include "basic_generator.hpp"

BasicGenerator::BasicGenerator(int seed) : terrainNoise{seed}
{}

BlockArgs BasicGenerator::generateBlockAt(int x, int y, int z)
{
    constexpr float increase = 3;
    float tn = terrainNoise.GetNoise((float)x, (float)y, (float)z);
    
    if (!(tn > 0.3 && tn < 0.8))
    {
        return BlockArgs{false, 2};
    }
    else
    {
        return BlockArgs{true, 0};
    }
}
