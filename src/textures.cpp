#include "textures.hpp"

Textures::Textures() : ids{}
{
	
}

Textures::~Textures()
{

}

void Textures::load(std::vector<std::string>& textures_str)
{
	for (auto& str : textures_str) {
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		stbi_set_flip_vertically_on_load(true);

		int width, height, channels;
		unsigned char* data = stbi_load(str.c_str(), &width, &height, &channels, 0);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Warning: Failed to load texture at " << str << std::endl;
		}

		stbi_image_free(data);

		ids.push_back(texture);
	}
}