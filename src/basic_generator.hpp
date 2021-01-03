#pragma once

#include <iostream>

#include "FastNoiseLite.h"
#include "chunk_generator.hpp"

struct BasicGenerator: public ChunkGenerator
{
    BasicGenerator(int seed = 0);

    BlockArgs generateBlockAt(int x, int y, int z) override;
private:
    FastNoiseLite terrainNoise;
};
