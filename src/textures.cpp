#include "textures.hpp"

Textures::Textures() : texture_ids{}
{
	
}

Textures::~Textures()
{

}

void Textures::load(std::vector<std::string>& textures_str)
{
    loadTextures(textures_str);
	
}

void Textures::loadTextures(std::vector<std::string>& textures_str)
{
    for (auto& str : textures_str) {
        
        // Set options for texture
        
        
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
		stbi_set_flip_vertically_on_load(true);

		int width, height, channels;
		unsigned char* data = stbi_load(str.c_str(), &width, &height, &channels, 0);

		if (data)
		{
            
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Warning: Failed to load texture at " << str << std::endl;
		}

		stbi_image_free(data);

		texture_ids.push_back(texture);
	}
}

void Textures::bindTexture(unsigned int id)
{
    glBindTexture(GL_TEXTURE_2D, texture_ids[id]);
}
