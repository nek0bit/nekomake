#include "block.hpp"

Block::Block(int id, int x, int y, int z)
    : faces{1, 1, 1, 1, 1, 1},
      x{static_cast<char>(x)},
      y{static_cast<char>(y)},
      z{static_cast<char>(z)},
      info{nullptr}
{
    std::vector<BlockInfo>& data = constants::block::blockInfo;

    // Check if the id exists
    auto found = std::find_if(data.begin(), data.end(),
                              [&id](const BlockInfo& compare) -> bool {
                                  return id == compare.id;
                              });
    
    if (found != data.end())
    {
        info = &*found;
    }
}

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
