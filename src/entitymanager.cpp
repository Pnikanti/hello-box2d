#include <glm/glm.hpp>
#include "entitymanager.h"
#include "physics.h"
#include "graphics.h"

std::vector<Entity*> EntityManager::Entities;

void EntityManager::CreateEntity(PhysicsComponent* physics, OpenGL::GraphicsComponent* graphics)
{
	Entities.emplace_back(new Entity(physics, graphics));
}

void EntityManager::CreateEntity(PhysicsComponent* physics, OpenGL::GraphicsComponent* graphics, glm::vec2 position, glm::vec2 size, float rotation)
{
	Entities.emplace_back(new Entity(physics, graphics, position, size, rotation));
}