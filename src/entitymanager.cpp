#include "entitymanager.h"
#include "physics.h"
#include "graphics.h"

std::vector<Entity*> EntityManager::Entities;

void EntityManager::CreateEntity(PhysicsComponent* physics, OpenGL::GraphicsComponent* graphics)
{
	Entities.emplace_back(new Entity(physics, graphics));
}

void EntityManager::CreateEntity(PhysicsComponent* physics, OpenGL::GraphicsComponent* graphics, glm::vec2 size, glm::vec2 position, float rotation)
{
	Entities.emplace_back(new Entity(physics, graphics, position, size, rotation));
}

void EntityManager::CreateEntity(PhysicsComponent* physics, OpenGL::GraphicsComponent* graphics, glm::vec2 size, glm::vec2 position, float rotation, glm::vec3 color)
{
	Entities.emplace_back(new Entity(physics, graphics, position, size, rotation, color));
}

void EntityManager::CreateEntity(PhysicsComponent* physics, OpenGL::GraphicsComponent* graphics, glm::vec2 size, glm::vec2 position, float rotation, glm::vec3 color, b2BodyType bodytype, float density, float friction, float restitution)
{
	Entities.emplace_back(new Entity(physics, graphics, position, size, rotation, color, bodytype, density, friction, restitution));

}
