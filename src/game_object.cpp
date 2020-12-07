#include "game_object.hpp"

GameObject::GameObject(Mesh* mesh, double x, double y, double z,
                       double rotX, double rotY, double rotZ,
                       double scaleX, double scaleY, double scaleZ)
	: pos{ x, y, z }, rot{ rotX, rotY, rotZ }, scale{ scaleX, scaleY, scaleZ },
      mesh{ mesh }
{
}

GameObject::~GameObject()
{}

void GameObject::render(Shader& shader, Textures& textures)
{
    if (mesh == nullptr)
    {
		throw MeshNullptr();
    }
	mesh->render(shader, textures, pos, rot, scale);
}
