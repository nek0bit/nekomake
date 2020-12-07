#include "block.hpp"

Block::Block(int x, int y, int z) : faces{1, 1, 1, 1, 1, 1}, x{x}, y{y}, z{z}
{}

Block::~Block()
{}

void Block::generateMesh(std::vector<float>& vertices, std::vector<int>& textures)
{
    for (size_t i = 0; i < faces.size(); ++i)
    {
        switch(i)
        {
        case 0: // Side 1
            if (faces[i])
                vertices.insert(vertices.end(), {
                        
                    });
            break;
        }
    }
}

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
