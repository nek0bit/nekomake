#include "chunk_mesh_generator.hpp"

void ChunkMeshGenerator::generateMesh(Block& block,
                                      ChunkOffset chunk_offsets,
                                      std::vector<Vertex>& vertices,
                                      std::vector<unsigned int>& ebo,
                                      unsigned int& eboIndex,
                                      TextureGrid& blockGrid)
{
    const BlockInfo& infoRef = *(block.info);
    bool sameSided = false;

    const float size = 0.5f;
   
    float offX = block.x + (chunk_offsets.x * constants::chunk::volume[0]);
    float offY = block.y + (chunk_offsets.y * constants::chunk::volume[1]);
    float offZ = block.z + (chunk_offsets.z * constants::chunk::volume[2]);


    // First insert the vertices with the predefined cube (if neccesary)
    bool hasFaces = false;

    std::array<TextureAtlas, 6> atlas = {};

    // Check if sameSided cube
    if (infoRef.sideTextures.size() > 1)
    {
        for (int i = 0; i < 5; ++i)
        {
            atlas[i] = blockGrid.getTextureAtlasAt(infoRef.sideTextures[i][0], infoRef.sideTextures[i][1]);
        }
    }
    else if (infoRef.sideTextures.size() == 1)
    {
        atlas[0] = blockGrid.getTextureAtlasAt(infoRef.sideTextures[0][0], infoRef.sideTextures[0][1]);
        sameSided = true;
    }

    if (std::find(block.faces.begin(), block.faces.end(), true) != block.faces.end())
    {
        if (sameSided)
        {
            // === EBO Cube === (Efficient for single sided textures)
            vertices.insert(vertices.end(), {
                    Vertex{offX-size, offY-size, offZ-size, atlas[0].beginX, atlas[0].beginY}, // 0
                    Vertex{offX+size, offY-size, offZ-size, atlas[0].endX, atlas[0].beginY}, // 1
                    Vertex{offX+size, offY+size, offZ-size, atlas[0].endX, atlas[0].endY}, // 2
                    Vertex{offX-size, offY+size, offZ-size, atlas[0].beginX, atlas[0].endY}, // 3
                
                    Vertex{offX-size, offY-size, offZ+size, atlas[0].beginX, atlas[0].beginY}, // 4
                    Vertex{offX+size, offY-size, offZ+size, atlas[0].endX, atlas[0].beginY}, // 5
                    Vertex{offX+size, offY+size, offZ+size, atlas[0].endX, atlas[0].endY}, // 6
                    Vertex{offX-size, offY+size, offZ+size, atlas[0].beginX, atlas[0].endY}, // 7
                
                    Vertex{offX-size, offY+size, offZ+size, atlas[0].endX, atlas[0].beginY}, // 8
                    Vertex{offX-size, offY+size, offZ-size, atlas[0].endX, atlas[0].endY}, // 9
                    Vertex{offX-size, offY-size, offZ-size, atlas[0].beginX, atlas[0].endY}, // 10
                    Vertex{offX-size, offY-size, offZ+size, atlas[0].beginX, atlas[0].beginY}, // 11
                
                    Vertex{offX+size, offY+size, offZ+size, atlas[0].endX, atlas[0].beginY}, // 12
                    Vertex{offX+size, offY-size, offZ-size, atlas[0].beginX, atlas[0].endY}, // 13
                    Vertex{offX+size, offY-size, offZ+size, atlas[0].beginX, atlas[0].beginY}, // 14
                
                    Vertex{offX+size, offY-size, offZ-size, atlas[0].endX, atlas[0].endY}, // 15
                    Vertex{offX+size, offY-size, offZ+size, atlas[0].endX, atlas[0].beginY}, // 16
                
                    Vertex{offX-size, offY+size, offZ+size, atlas[0].beginX, atlas[0].beginY}, // 17 
                });
        }
        else
        {
            // === VBO-like Cube === (Less effeicient then pure EBO's, but useful for multi-sided textures)
            vertices.insert(vertices.end(), {
                    Vertex{offX-size, offY-size, offZ-size,  atlas[0].beginX, atlas[0].beginY},
                    Vertex{offX+size, offY-size, offZ-size,  atlas[0].endX, atlas[0].beginY},
                    Vertex{offX+size, offY+size, offZ-size,  atlas[0].endX, atlas[0].endY},
                    Vertex{offX+size, offY+size, offZ-size,  atlas[0].endX, atlas[0].endY},
                    Vertex{offX-size, offY+size, offZ-size,  atlas[0].beginX, atlas[0].endY},
                    Vertex{offX-size, offY-size, offZ-size,  atlas[0].beginX, atlas[0].beginY},

                    Vertex{offX-size, offY-size, offZ+size,  atlas[1].beginX, atlas[1].beginY},
                    Vertex{offX+size, offY-size, offZ+size,  atlas[1].endX, atlas[1].beginY},
                    Vertex{offX+size, offY+size, offZ+size,  atlas[1].endX, atlas[1].endY},
                    Vertex{offX+size, offY+size, offZ+size,  atlas[1].endX, atlas[1].endY},
                    Vertex{offX-size, offY+size, offZ+size,  atlas[1].beginX, atlas[1].endY},
                    Vertex{offX-size, offY-size, offZ+size,  atlas[1].beginX, atlas[1].beginY},

                    Vertex{offX-size, offY+size, offZ+size,  atlas[2].endX, atlas[2].beginY},
                    Vertex{offX-size, offY+size, offZ-size,  atlas[2].endX, atlas[2].endY},
                    Vertex{offX-size, offY-size, offZ-size,  atlas[2].beginX, atlas[2].endY},
                    Vertex{offX-size, offY-size, offZ-size,  atlas[2].beginX, atlas[2].endY},
                    Vertex{offX-size, offY-size, offZ+size,  atlas[2].beginX, atlas[2].beginY},
                    Vertex{offX-size, offY+size, offZ+size,  atlas[2].endX, atlas[2].beginY},

                    Vertex{offX+size, offY+size, offZ+size,  atlas[3].endX, atlas[3].beginY},
                    Vertex{offX+size, offY+size, offZ-size,  atlas[3].endX, atlas[3].endY},
                    Vertex{offX+size, offY-size, offZ-size,  atlas[3].beginX, atlas[3].endY},
                    Vertex{offX+size, offY-size, offZ-size,  atlas[3].beginX, atlas[3].endY},
                    Vertex{offX+size, offY-size, offZ+size,  atlas[3].beginX, atlas[3].beginY},
                    Vertex{offX+size, offY+size, offZ+size,  atlas[3].endX, atlas[3].beginY},

                    Vertex{offX-size, offY-size, offZ-size,  atlas[4].beginX, atlas[4].endY},
                    Vertex{offX+size, offY-size, offZ-size,  atlas[4].endX, atlas[4].endY},
                    Vertex{offX+size, offY-size, offZ+size,  atlas[4].endX, atlas[4].beginY},
                    Vertex{offX+size, offY-size, offZ+size,  atlas[4].endX, atlas[4].beginY},
                    Vertex{offX-size, offY-size, offZ+size,  atlas[4].beginX, atlas[4].beginY},
                    Vertex{offX-size, offY-size, offZ-size,  atlas[4].beginX, atlas[4].endY},

                    Vertex{offX-size, offY+size, offZ-size,  atlas[5].beginX, atlas[5].endY},
                    Vertex{offX+size, offY+size, offZ-size,  atlas[5].endX, atlas[5].endY},
                    Vertex{offX+size, offY+size, offZ+size,  atlas[5].endX, atlas[5].beginY},
                    Vertex{offX+size, offY+size, offZ+size,  atlas[5].endX, atlas[5].beginY},
                    Vertex{offX-size, offY+size, offZ+size,  atlas[5].beginX, atlas[5].beginY},
                    Vertex{offX-size, offY+size, offZ-size,  atlas[5].beginX, atlas[5].endY}
                });
        }
        hasFaces = true;
    }

    if (hasFaces)
    {
        for (size_t i = 0; i < block.faces.size(); ++i)
        {
            std::vector<unsigned int> newVec;
            
            switch(i)
            {
            case 0: // Side 1
                if (block.faces[i])
                {
                    newVec = vecAddNum(eboIndex,
                                       sameSided ? std::vector<unsigned>{0, 1, 2, 2, 3, 0}
                                       : std::vector<unsigned>{0, 1, 2, 3, 4, 5});
                }
                
                 break;
            case 1: // Side 2
                if (block.faces[i])
                {                
                    newVec = vecAddNum(eboIndex,
                                       sameSided ? std::vector<unsigned>{4, 5, 6, 6, 7, 4}
                                       : std::vector<unsigned>{6, 7, 8, 9, 10, 11});
                }
                break;
            case 2: // Side 3
                if (block.faces[i])
                {
                    newVec = vecAddNum(eboIndex,
                                       sameSided ? std::vector<unsigned>{8, 9, 10, 10, 11, 8}
                                       : std::vector<unsigned>{12, 13, 14, 15, 16, 17});
                }
                break;
            case 3: // Side 4
                if (block.faces[i])
                {
                    newVec = vecAddNum(eboIndex,
                                       sameSided ? std::vector<unsigned>{12, 2, 13, 13, 14, 12}
                                       : std::vector<unsigned>{18, 19, 20, 21, 22, 23});
                }
                break;
            case 4: // Side 5
                if (block.faces[i])
                {
                    newVec = vecAddNum(eboIndex,
                                       sameSided ? std::vector<unsigned>{10, 15, 16, 16, 4, 10}
                                       : std::vector<unsigned>{24, 25, 26, 27, 28, 29});
                }
                break;
            case 5: // Side 6
                if (block.faces[i])
                {
                    newVec = vecAddNum(eboIndex,
                                       sameSided ? std::vector<unsigned>{3, 2, 12, 12, 17, 3}
                                       : std::vector<unsigned>{30, 31, 32, 33, 34, 35});
                }
                break;
            default:
                break;
            }

            if (block.faces[i])
            {
                ebo.insert(ebo.end(), newVec.begin(), newVec.end());
            }
        }

        // Increment the ebo index for future cubes
        eboIndex += sameSided ? 18 : 36; // MAX --- ebo = 17 : vbo = 35
    }
}


std::vector<unsigned int> ChunkMeshGenerator::vecAddNum(int to_add, std::vector<unsigned int> vec)
{
    for (size_t i = 0; i < vec.size(); ++i)
    {
        vec[i] += to_add;
    }
    return vec;
}
