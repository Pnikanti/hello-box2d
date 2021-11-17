#include <glm/glm.hpp>
#include "entitymanager.h"
#include "physics.h"
#include "graphics.h"

std::vector<Entity> EntityManager::Entities(std::vector<Entity>(10));

void EntityManager::CreateEntity(PhysicsComponent* physics, OpenGL::GraphicsComponent* graphics)
{
	Entities.emplace_back(Entity(physics, graphics));
}

void EntityManager::CreateEntity(PhysicsComponent* physics, OpenGL::GraphicsComponent* graphics, glm::vec2 size, glm::vec2 position, float rotation)
{
	Entity e = Entity(physics, graphics);
	e.SetAttributes(position, size, rotation);
	Entities.emplace_back(e);
}