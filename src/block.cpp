#include "block.hpp"

Block::Block(int x, int y, int z) : faces{1, 1, 1, 1, 1, 1}, x{x}, y{y}, z{z}
{}

Block::~Block()
{}

void Block::generateMesh(std::vector<float>& vertices,
                         std::vector<unsigned int>& textures,
                         std::vector<unsigned int>& ebo,
                         unsigned int& eboIndex)
{
    const float offX = x * constants::block::blockSize;
    const float offY = y * constants::block::blockSize;
    const float offZ = z * constants::block::blockSize;

    // First insert the vertices with the predefined cube
    vertices.insert(vertices.end(), {
            offX-1.0f, offY-1.0f, offZ-1.0f, 0.0f, 0.0f, // 0
            offX+1.0f, offY-1.0f, offZ-1.0f, 1.0f, 0.0f, // 1
            offX+1.0f, offY+1.0f, offZ-1.0f, 1.0f, 1.0f, // 2
            offX-1.0f, offY+1.0f, offZ-1.0f, 0.0f, 1.0f, // 3

            offX-1.0f, offY-1.0f, offZ+1.0f, 0.0f, 0.0f, // 4
            offX+1.0f, offY-1.0f, offZ+1.0f, 1.0f, 0.0f, // 5
            offX+1.0f, offY+1.0f, offZ+1.0f, 1.0f, 1.0f, // 6
            offX-1.0f, offY+1.0f, offZ+1.0f, 0.0f, 1.0f, // 7

            offX-1.0f, offY+1.0f, offZ+1.0f, 1.0f, 0.0f, // 8
            offX-1.0f, offY+1.0f, offZ-1.0f, 1.0f, 1.0f, // 9
            offX-1.0f, offY-1.0f, offZ-1.0f, 0.0f, 1.0f, // 10
            offX-1.0f, offY-1.0f, offZ+1.0f, 0.0f, 0.0f, // 11

            offX+1.0f, offY+1.0f, offZ+1.0f, 1.0f, 0.0f, // 12
            offX+1.0f, offY-1.0f, offZ-1.0f, 0.0f, 1.0f, // 13
            offX+1.0f, offY-1.0f, offZ+1.0f, 0.0f, 0.0f, // 14

            offX+1.0f, offY-1.0f, offZ-1.0f, 1.0f, 1.0f, // 15
            offX+1.0f, offY-1.0f, offZ+1.0f, 1.0f, 0.0f, // 16

            offX-1.0f, offY+1.0f, offZ+1.0f, 0.0f, 0.0f, // 17
        });
    
    for (size_t i = 0; i < faces.size(); ++i)
    {
        switch(i)
        {
        case 0: // Side 1
            if (faces[i])
            {
                std::vector<unsigned int> newVec = vecAddNum(eboIndex, {0, 1, 2, 2, 3, 0,
                                                                        4, 5, 6, 6, 7, 4,
                                                                        8, 9, 10, 10, 11, 8,
                                                                        12, 2, 13, 13, 14, 12,
                                                                        10, 15, 16, 16, 4, 10,
                                                                        3, 2, 12, 12, 17, 3});
                ebo.insert(ebo.end(), newVec.begin(), newVec.end());
                eboIndex += 17; // Max number in eboIndex is 17
                textures.insert(textures.end(), {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
            }
            break;
        case 1: // Side 2
            if (faces[i])
            {                
                std::vector<unsigned int> newVec = vecAddNum(eboIndex, {0, 1, 2, 2, 3, 0,
                                                                        4, 5, 6, 6, 7, 4,
                                                                        8, 9, 10, 10, 11, 8,
                                                                        12, 2, 13, 13, 14, 12,
                                                                        10, 15, 16, 16, 4, 10,
                                                                        3, 2, 12, 12, 17, 3});
                ebo.insert(ebo.end(), newVec.begin(), newVec.end());
                eboIndex += 17; // Max number in eboIndex is 17
                textures.insert(textures.end(), {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
            }
            break;
        case 2: // Side 3
            if (faces[i])
            {
                std::vector<unsigned int> newVec = vecAddNum(eboIndex, {0, 1, 2, 2, 3, 0,
                                                                        4, 5, 6, 6, 7, 4,
                                                                        8, 9, 10, 10, 11, 8,
                                                                        12, 2, 13, 13, 14, 12,
                                                                        10, 15, 16, 16, 4, 10,
                                                                        3, 2, 12, 12, 17, 3});
                ebo.insert(ebo.end(), newVec.begin(), newVec.end());
                eboIndex += 17; // Max number in eboIndex is 17
                textures.insert(textures.end(), {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
            }
            break;
        case 3: // Side 4
            if (faces[i])
            {
                std::vector<unsigned int> newVec = vecAddNum(eboIndex, {0, 1, 2, 2, 3, 0,
                                                                        4, 5, 6, 6, 7, 4,
                                                                        8, 9, 10, 10, 11, 8,
                                                                        12, 2, 13, 13, 14, 12,
                                                                        10, 15, 16, 16, 4, 10,
                                                                        3, 2, 12, 12, 17, 3});
                ebo.insert(ebo.end(), newVec.begin(), newVec.end());
                eboIndex += 17; // Max number in eboIndex is 17
                textures.insert(textures.end(), {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
            }
            break;
        case 4: // Side 5
            if (faces[i])
            {
                std::vector<unsigned int> newVec = vecAddNum(eboIndex, {0, 1, 2, 2, 3, 0,
                                                                        4, 5, 6, 6, 7, 4,
                                                                        8, 9, 10, 10, 11, 8,
                                                                        12, 2, 13, 13, 14, 12,
                                                                        10, 15, 16, 16, 4, 10,
                                                                        3, 2, 12, 12, 17, 3});
                ebo.insert(ebo.end(), newVec.begin(), newVec.end());
                eboIndex += 17; // Max number in eboIndex is 17
                textures.insert(textures.end(), {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
            }
            break;
        case 5: // Side 6
            if (faces[i])
            {
                std::vector<unsigned int> newVec = vecAddNum(eboIndex, {0, 1, 2, 2, 3, 0,
                                                                        4, 5, 6, 6, 7, 4,
                                                                        8, 9, 10, 10, 11, 8,
                                                                        12, 2, 13, 13, 14, 12,
                                                                        10, 15, 16, 16, 4, 10,
                                                                        3, 2, 12, 12, 17, 3});
                ebo.insert(ebo.end(), newVec.begin(), newVec.end());
                eboIndex += 17; // Max number in eboIndex is 17
                textures.insert(textures.end(), {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
            }
            break;
        default:
            break;
        }
    }
}

std::vector<unsigned int> Block::vecAddNum(int to_add, std::vector<unsigned int> vec)
{
    for (size_t i = 0; i < vec.size(); ++i)
    {
        vec[i] += to_add;
    }
    return vec;
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
