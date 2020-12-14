#include "mesh.hpp"

constexpr int count = 5;
constexpr int t_indices = 3;

Mesh::Mesh() : texture{0}, VBO{0}, EBO{0}, VAO{ 0 }, indiceSize{ 0 }
{
}

Mesh::~Mesh()
{}


void Mesh::init(std::vector<Vertex> vertices,
                std::vector<unsigned int> indices)
{
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Generate VAO
	glGenVertexArrays(1, &VAO);

    bindBuffer(vertices, indices);
	// Attributes

    // TODO move this to opengl init method
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

}

void Mesh::bindBuffer(std::vector<Vertex>& vertices, std::vector<unsigned int> indices)
{
    indiceSize = indices.size();
    
    glBindVertexArray(VAO);
    
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(&indices[0]), &indices[0], GL_STATIC_DRAW);
}

void Mesh::render(Shader& shader,
                  Textures& textures,
                  glm::vec3& transformVertex,
                  glm::vec3& rotateVertex,
                  glm::vec3& scaleVertex)
{
    
	glBindVertexArray(VAO);

	glm::mat4 model{ 1.0f };
	//model = glm::translate(model, transformVertex);

    // Rotate by x, y, and z axis
    //model = glm::rotate(model, rotateVertex.x, glm::vec3(1.0f, 0.0f, 0.0f));
    //model = glm::rotate(model, rotateVertex.y, glm::vec3(0.0f, 1.0f, 0.0f));
    //model = glm::rotate(model, rotateVertex.z, glm::vec3(0.0f, 0.0f, 1.0f));

    //model = glm::scale(model, scaleVertex);

    shader.setUniformMatrix4fv(shader.modelLoc, glm::value_ptr(model));

    textures.bindTexture(texture);

    
    glDrawElements(GL_TRIANGLES, indiceSize, GL_UNSIGNED_INT, 0);
    
	glBindVertexArray(0);
}
