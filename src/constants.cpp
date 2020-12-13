#include "constants.hpp"

namespace constants::block
{
    Mesh* blockMesh = nullptr; // Because it is used so often
    double blockSize = 1.0;
    int texWidth = 2;
    int texHeight = 1;
    int pixelSize = 32;

    std::vector<BlockInfo> blockInfo = {
        BlockInfo{BLOCK_DIRT, "Dirt", {{0,0}, {1,0}, {0,0}, {1,0}, {0,0}, {1,0}}}
    };
    
}

namespace constants::chunk
{}
