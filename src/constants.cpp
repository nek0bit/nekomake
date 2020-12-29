#include "constants.hpp"

namespace constants::block
{
    Mesh* blockMesh = nullptr; // Because it is used so often
    double blockSize = 1.0;
    int texWidth = 3;
    int texHeight = 1;
    int pixelSize = 32;

    std::vector<BlockInfo> blockInfo = {
        {BLOCK_MOON_SOIL, "Moon Soil", {{0,0}}},
        {BLOCK_STONE, "Fallen Stone", {{1,0}}},
    };
    
}

namespace constants::chunk
{}
