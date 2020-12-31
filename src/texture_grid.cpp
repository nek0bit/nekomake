#include "texture_grid.hpp"

TextureGrid::TextureGrid(int textureWidth, int textureHeight, int mapWidth, int mapHeight)
    : textureWidth{textureWidth}, textureHeight{textureHeight}, mapWidth{mapWidth*textureWidth}, mapHeight{mapHeight*textureHeight}
{}

TextureAtlas TextureGrid::getTextureAtlasAt(float x, float y)
{
    const float sizeX = ((x+0.5) * textureWidth);
    const float sizeY = ((y+0.5) * textureHeight);
    const float beginX = (sizeX+textureWidth) / mapWidth;
    const float endX = sizeX / mapWidth;
    const float beginY = (sizeY+textureHeight) / mapHeight;
    const float endY = sizeY / mapHeight;
    
    return TextureAtlas{beginX, endX, beginY, endY};
};
