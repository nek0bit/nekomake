#pragma once

#include <iostream>
#include <vector>

#include "constants.cpp"
#include "game_object.hpp"

struct Block: public GameObject
{
    Block(int x = 0, int y = 0, int z = 0);

    setX(int x);
    setY(int y);
    setZ(int z);
private:
    int x;
    int y;
    int z;
};
