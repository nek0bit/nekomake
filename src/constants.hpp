#pragma once

#include <array>

#include "mesh.hpp"

typedef std::array<int, 3> chunkVolume_t;

enum mesh_enum
{
    MESH_BLOCK
};

enum keys_enum
{
	KEY_ESCAPE = 0,
	KEY_W,
	KEY_A,
	KEY_S,
	KEY_D,
    KEY_R,
	KEY_SPACE,
	KEY_LEFT_SHIFT
};

namespace constants
{    
    namespace block
    {
        extern Mesh* blockMesh;
        extern double blockSize;
    }
    
    namespace chunk
    {
        /* extern constexpr isn't valid, so I defined them here */
        constexpr chunkVolume_t volume = {8, 300, 8};
        constexpr int splitCount = 30;
    }
}
