#pragma once

#include <iostream>
#include <vector>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "stb_image.h"


struct Textures {
	Textures();
	~Textures();

	void load(std::vector<std::string>& textures_str);

    void bindTexture(unsigned int id);

	std::vector<unsigned int> texture_ids;
private:
    void loadTextures(std::vector<std::string>& textures_str);
};
