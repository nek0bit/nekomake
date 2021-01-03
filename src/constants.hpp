#pragma once

#include <string>
#include <array>

#include "blockinfo.hpp"
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
        extern int texWidth, texHeight, pixelSize;
        extern std::vector<BlockInfo> blockInfo;
    }
    
    namespace chunk
    {
        // Dimensions of a 3D chunk
        constexpr chunkVolume_t volume = {6, 6, 6};
    }
}
