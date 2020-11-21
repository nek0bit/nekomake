#include "shader.hpp"

Shader::Shader() : program{ 0 }
{}

void Shader::load(const std::string vertShaderFilename, const std::string fragShaderFilename)
{
	std::ifstream vertShader_f, fragShader_f;
	vertShader_f.open(vertShaderFilename);
	fragShader_f.open(fragShaderFilename);

	std::stringstream vertShader_stream, fragShader_stream;
	vertShader_stream << vertShader_f.rdbuf();
	fragShader_stream << fragShader_f.rdbuf();

	std::string vertShader_str = vertShader_stream.str(), fragShader_str = fragShader_stream.str();

	const char *vertShader = vertShader_str.c_str(), *fragShader = fragShader_str.c_str();

	program = glCreateProgram();
	
	// Temporary shaders
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Source and compile shaders
	glShaderSource(vertexShader, 1, &vertShader, NULL);
	glShaderSource(fragmentShader, 1, &fragShader, NULL);
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	// Check if success
	int success;
	std::array<unsigned int, 2> grouping = { vertexShader, fragmentShader };
	std::for_each(grouping.begin(), grouping.end(), [&](unsigned int& id) {
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			char info[256];
			glGetShaderInfoLog(id, 256, NULL, info);
			std::cout << "Shader compilation failed: " << info << std::endl;
		}
		else {
			glAttachShader(program, id);
		}
		});

	// Link shaders
	glLinkProgram(program);

	// Check if that succeeded
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		char info[256];
		glGetProgramInfoLog(program, 256, NULL, info);
		std::cout << "Shader program linking failed: " << info << std::endl;
	}

	std::for_each(grouping.begin(), grouping.end(), [&](unsigned int& id) {
		glDeleteShader(id);
		});
}

Shader::~Shader()
{
	glDeleteShader(program);
}

void Shader::use()
{
	glUseProgram(program);
}

unsigned int Shader::getUniform(const std::string uniform)
{
	return glGetUniformLocation(program, uniform.c_str());
}

void Shader::setUniformMatrix4fv(unsigned int location, const GLfloat* value)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, value);
}