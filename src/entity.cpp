#include <glm/gtx/string_cast.hpp>
#include "entity.h"
#include "log.h"
#include "physics.h"

Entity::Entity(PhysicsComponent* physicsComponent, OpenGL::GraphicsComponent* graphicsComponent) :
	input(nullptr),
	graphics(graphicsComponent),
	physics(physicsComponent),
	position(glm::vec2(0.0f)),
	direction(glm::vec2(0.0f)),
	size(glm::vec2(3.0f, 3.0f)),
	speed(10.0f / 100)
{}

void Entity::Advance()
{
	LOGGER_TRACE("Position: {0}", glm::to_string(position));
	position = position + (glm::vec2(speed) * direction);
}

void Entity::Draw()
{
	graphics->Draw(*this);
}

void Entity::UpdatePhysics()
{
	physics->Update(*this);
}