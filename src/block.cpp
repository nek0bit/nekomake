#include "block.hpp"

Block::Block(int x, int y, int z) : GameObject{constants::blockMesh,
    0.0, 0.0, 0.0,
    0.0, 0.0, 0.0,
    1.0, 1.0, 1.0}, x{x}, y{y}, z{z}
{
    setX(x);
    setY(y);
    setZ(z);
}

void Block::updateFaces(cubeFaces_t faces)
{
    toggles.resize(12);
    for (int i = 0; i < faces.size(); ++i)
    {
        switch(i)
        {
        case 0: // SIDE 1
            toggles[0] = faces[i];
            toggles[1] = faces[i];
            break;
        case 1: // SIDE 2
            toggles[2] = faces[i];
            toggles[3] = faces[i];
            break;
        case 2: // SIDE 3
            toggles[4] = faces[i];
            toggles[5] = faces[i];
            break;
        case 3: // SIDE 4
            toggles[6] = faces[i];
            toggles[7] = faces[i];
            break;
        case 4: // SIDE 5 - bottom
            toggles[8] = faces[i];
            toggles[9] = faces[i];
            break;
        case 5: // SIDE 6 - top
            toggles[10] = faces[i];
            toggles[11] = faces[i];
            break;
        default:
            break;
        }
    }
}

void Block::setX(int x)
{
    this->x = x;
    pos.x = x * constants::blockSize;
}

void Block::setY(int y)
{
    this->y = y;
    pos.y = y * constants::blockSize;
}

void Block::setZ(int z)
{
    this->z = z;
    pos.z = z * constants::blockSize;
}
