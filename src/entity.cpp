#include <glm/gtx/string_cast.hpp>
#include "entity.h"
#include "log.h"
#include "physics.h"

Entity::Entity(PhysicsComponent* physicsComponent, OpenGL::GraphicsComponent* graphicsComponent) :
	input(nullptr),
	graphics(graphicsComponent),
	physics(physicsComponent)
{
	physics->CreateEntity(glm::vec2(0.0f), glm::vec2(1.0f), 0.0f);
}

glm::vec2 Entity::GetSize() { return physics->GetSize() * 2.0f; }
glm::vec2 Entity::GetPosition() { return physics->GetPosition(); }
float Entity::GetRotationDegrees() { return physics->GetRotationDegrees(); }
float Entity::GetRotationRadians() { return physics->GetRotationRadians(); }

void Entity::SetAttributes(glm::vec2 position, glm::vec2 size, float rotation)
{
	physics->CreateEntity(position, size, glm::radians(rotation));
}

void Entity::Advance()
{
	physics->Update();
}

void Entity::Draw()
{
	graphics->Draw(*this);
}