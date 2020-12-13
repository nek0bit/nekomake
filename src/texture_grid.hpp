#pragma once

#include <iostream>

struct TextureAtlas
{
    float beginX;
    float endX;
    float beginY;
    float endY;
};

class TextureGrid
{
public:
    TextureGrid(int textureWidth, int textureHeight, int mapWidth, int mapHeight);

    TextureAtlas getTextureAtlasAt(float x, float y);
    
private:
    int textureWidth, textureHeight;
    int mapWidth, mapHeight;
};
