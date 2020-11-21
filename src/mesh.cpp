#include "mesh.hpp"

Mesh::Mesh(unsigned int* VBO) : vertices{ }, VBO{ VBO }, VAO{ 0 }, count{ 0 }
{
}

Mesh::~Mesh()
{}


void Mesh::init(std::vector<float> &vertices)
{
	count = vertices.size() / 5;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(&vertices[0]), &vertices[0], GL_DYNAMIC_DRAW);
	// Attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void Mesh::render(Shader &shader, glm::vec3 &transformVertex, float rotate, glm::vec3 &rotateVertex)
{
	glBindVertexArray(VAO);

	glm::mat4 model{ 1.0f };
	model = glm::translate(model, transformVertex);
	model = glm::rotate(model, rotate, rotateVertex);
	//shader.setUniformMatrix4fv(shader.modelLoc, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, count);
}