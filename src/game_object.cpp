#include "game_object.hpp"

GameObject::GameObject(Mesh* mesh, double x, double y, double z, double rotX, double rotY, double rotZ)
	: pos{ x, y, z }, rot{ rotX, rotY, rotZ }, mesh{ mesh }
{
	if (mesh == nullptr)
	{
		throw MeshNullptr();
	}
}

GameObject::~GameObject()
{}

void GameObject::render(Shader& shader)
{
	mesh->render(shader, pos, rot);
}
