#pragma once

#include "FastNoiseLite.h"
#include "chunk_generator.hpp"

struct BasicGenerator: public ChunkGenerator
{
    BasicGenerator(int seed = 0);

    BlockArgs generateBlockAt(int x, int y, int z) const override;
};
