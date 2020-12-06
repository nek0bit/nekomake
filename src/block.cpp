#include "block.hpp"

Block::Block(int x, int y, int z) : GameObject{constants::blockMesh,
    0.0, 0.0, 0.0,
    0.0, 0.0, 0.0,
    1.0, 1.0, 1.0}, x{x}, y{y}, z{z};
{
    setX(x);
    setY(y);
    setZ(z);
}
