#pragma once

/*
 * A polymorphic class that can be used for the world's chunk generation.
 * Will most likely handle structures later
 */

struct BlockArgs
{
    bool emptyBlock;
    int id;
};

struct ChunkGenerator
{
    ChunkGenerator(int seed = 0);
    virtual ~ChunkGenerator();

    virtual BlockArgs generateBlockAt(int, int, int);
    
    const int seed;
};
