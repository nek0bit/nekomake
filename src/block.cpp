#include "block.hpp"

Block::Block(int x, int y, int z) : x{x}, y{y}, z{z}
{}

Block::~Block()
{}

bool Block::operator<(const Block& b) const
{
    return x < b.x && y < b.y && z < b.z;
}

bool Block::operator>(const Block& b) const
{
    return x > b.x && y > b.y && z > b.z;
}

bool Block::compare(int com_x, int com_y, int com_z) const
{
    return x == com_x && y == com_y && z == com_z;
}
