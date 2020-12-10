#include "block.hpp"

Block::Block(int x, int y, int z) : faces{1, 1, 1, 1, 1, 1}, x{x}, y{y}, z{z}
{}

Block::~Block()
{}

void Block::generateMesh(std::vector<Vertex>& vertices,
                         std::vector<unsigned int>& textures,
                         std::vector<unsigned int>& ebo,
                         unsigned int& eboIndex)
{
    float offX = x;
    float offY = y;
    float offZ = z;

    const float size = 0.5f;

    // First insert the vertices with the predefined cube (if neccesary)
    bool hasFaces = false;

    if (std::find(faces.begin(), faces.end(), true))
    {
        // A dynamic cube
        vertices.insert(vertices.end(), {
                Vertex{offX-size, offY-size, offZ-size, 0.0f, 0.0f}, // 0
                Vertex{offX+size, offY-size, offZ-size, 1.0f, 0.0f}, // 1
                Vertex{offX+size, offY+size, offZ-size, 1.0f, 1.0f}, // 2
                Vertex{offX-size, offY+size, offZ-size, 0.0f, 1.0f}, // 3
                
                Vertex{offX-size, offY-size, offZ+size, 0.0f, 0.0f}, // 4
                Vertex{offX+size, offY-size, offZ+size, 1.0f, 0.0f}, // 5
                Vertex{offX+size, offY+size, offZ+size, 1.0f, 1.0f}, // 6
                Vertex{offX-size, offY+size, offZ+size, 0.0f, 1.0f}, // 7
                
                Vertex{offX-size, offY+size, offZ+size, 1.0f, 0.0f}, // 8
                Vertex{offX-size, offY+size, offZ-size, 1.0f, 1.0f}, // 9
                Vertex{offX-size, offY-size, offZ-size, 0.0f, 1.0f}, // 10
                Vertex{offX-size, offY-size, offZ+size, 0.0f, 0.0f}, // 11
                
                Vertex{offX+size, offY+size, offZ+size, 1.0f, 0.0f}, // 12
                Vertex{offX+size, offY-size, offZ-size, 0.0f, 1.0f}, // 13
                Vertex{offX+size, offY-size, offZ+size, 0.0f, 0.0f}, // 14
                
                Vertex{offX+size, offY-size, offZ-size, 1.0f, 1.0f}, // 15
                Vertex{offX+size, offY-size, offZ+size, 1.0f, 0.0f}, // 16
                
                Vertex{offX-size, offY+size, offZ+size, 0.0f, 0.0f}, // 17
            });
        hasFaces = true;
    }

    if (hasFaces)
    {
        for (size_t i = 0; i < faces.size(); ++i)
        {            
            switch(i)
            {
            case 0: // Side 1
                if (faces[i])
                {
                    std::vector<unsigned int> newVec = vecAddNum(eboIndex, {0, 1, 2, 2, 3, 0,});
                    ebo.insert(ebo.end(), newVec.begin(), newVec.end());
                    textures.insert(textures.end(), {0, 1});
                }
                
                break;
            case 1: // Side 2
                if (faces[i])
                {                
                    std::vector<unsigned int> newVec = vecAddNum(eboIndex, {4, 5, 6, 6, 7, 4});
                    ebo.insert(ebo.end(), newVec.begin(), newVec.end());
                    textures.insert(textures.end(), {0, 1});
                }
                break;
            case 2: // Side 3
                if (faces[i])
                {
                    std::vector<unsigned int> newVec = vecAddNum(eboIndex, {8, 9, 10, 10, 11, 8
                        });
                    ebo.insert(ebo.end(), newVec.begin(), newVec.end());
                    textures.insert(textures.end(), {0, 1});
                }
                break;
            case 3: // Side 4
                if (faces[i])
                {
                    std::vector<unsigned int> newVec = vecAddNum(eboIndex, {12, 2, 13, 13, 14, 12});
                    ebo.insert(ebo.end(), newVec.begin(), newVec.end());
                    textures.insert(textures.end(), {0, 1});
                }
                break;
            case 4: // Side 5
                if (faces[i])
                {
                    std::vector<unsigned int> newVec = vecAddNum(eboIndex, {10, 15, 16, 16, 4, 10});
                    ebo.insert(ebo.end(), newVec.begin(), newVec.end());
                    textures.insert(textures.end(), {0, 1});
                }
                break;
            case 5: // Side 6
                if (faces[i])
                {
                    std::vector<unsigned int> newVec = vecAddNum(eboIndex, {3, 2, 12, 12, 17, 3});
                    ebo.insert(ebo.end(), newVec.begin(), newVec.end());
                    textures.insert(textures.end(), {0, 1});
                }
                break;
            default:
                break;
            }
        }

        // Increment the ebo index for future cubes
        eboIndex += 18; // Max number in ebo for the cube is 17
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
