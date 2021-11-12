#include "physics.h"
#include "entity.h"

PhysicsComponent::PhysicsComponent()
	: PhysicsWorld(nullptr)
{
	//PhysicsWorld = new b2World({ 0.0f, -9.8f });
}
PhysicsComponent::~PhysicsComponent()
{
	//delete PhysicsWorld;
	//PhysicsWorld = nullptr;
}

void PhysicsComponent::Update(Entity& entity)
{

}