#include "mesh.hpp"

constexpr int count = 5;
constexpr int indices = 3;

Mesh::Mesh(unsigned int* VBO) : VBO{ VBO }, VAO{ 0 }, amount{ 0 }
{
}

Mesh::~Mesh()
{}


void Mesh::init(std::vector<float> vertices, std::vector<int> texture_ids)
{
    amount = vertices.size() / count;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(&vertices[0]), &vertices[0], GL_DYNAMIC_DRAW);
	// Attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

    this->texture_ids = texture_ids;
}

void Mesh::render(Shader& shader,
                  Textures& textures,
                  glm::vec3& transformVertex,
                  glm::vec3& rotateVertex,
                  glm::vec3& scaleVertex)
{
	glBindVertexArray(VAO);

	glm::mat4 model{ 1.0f };
	model = glm::translate(model, transformVertex);

    // Rotate by x, y, and z axis
    model = glm::rotate(model, rotateVertex.x, glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, rotateVertex.y, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, rotateVertex.z, glm::vec3(0.0f, 0.0f, 1.0f));

    model = glm::scale(model, scaleVertex);

    shader.setUniformMatrix4fv(shader.modelLoc, glm::value_ptr(model));

    for (int i = 0; i < amount/indices; i++)
    {
        textures.bindTexture(texture_ids[i]);
        std::cout << i * indices << std::endl;
        glDrawArrays(GL_TRIANGLES, i*indices, indices);
    }
    
	glBindVertexArray(0);
}
