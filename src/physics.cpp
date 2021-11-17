#include <glm/gtx/string_cast.hpp>
#include "physics.h"
#include "entity.h"
#include "app.h"
#include "log.h"

b2World* PhysicsWorld::World = nullptr;

PhysicsWorld::PhysicsWorld() :
	VelocityIterations(6), 
	PositionIterations(2)
{
	World = new b2World({ 0.0f, -9.8f });
}

PhysicsWorld::~PhysicsWorld()
{
	delete World;
	World = nullptr;
}

void PhysicsWorld::Update()
{
	auto bodies = World->GetBodyCount();
	LOGGER_TRACE("Updating \"{0}\" bodies!", bodies);
	World->Step(Application::TimeStep, VelocityIterations, PositionIterations);
}

PhysicsComponent::PhysicsComponent() :
	Position(glm::vec2(0.0f, 0.0f)),
	Size(glm::vec2(1.0f, 1.0f)),
	Rotation(0.0f),
	Body(nullptr),
	Fixture(nullptr),
	BodyDefinition(),
	Shape(),
	FixtureDefinition() 
{
	LOGGER_TRACE("PhysicsComponent constructor called");
}

void PhysicsComponent::CreateEntity(glm::vec2 position, glm::vec2 size, float rotation)
{
	LOGGER_TRACE("CreateEntity called");
	if (Body != nullptr)
	{
		PhysicsWorld::World->DestroyBody(Body);
		Body = nullptr;
	}

	Size = size;
	Position = position;
	Rotation = rotation; // must be passed as radians!

	Shape.SetAsBox(Size.x, Size.y);
	FixtureDefinition.shape = &Shape;
	BodyDefinition.position.Set(Position.x, Position.y);

	Body = PhysicsWorld::World->CreateBody(&BodyDefinition);
	Body->SetTransform(Body->GetPosition(), Rotation);
	Fixture = Body->CreateFixture(&FixtureDefinition);
}

glm::vec2 PhysicsComponent::GetPosition()
{
	return Position;
}

float PhysicsComponent::GetRotationRadians()
{
	return Rotation;
}

float PhysicsComponent::GetRotationDegrees()
{
	return glm::degrees(Rotation);
}

glm::vec2 PhysicsComponent::GetSize()
{
	return Size;
}

void PhysicsComponent::Update() {}

PhysicsStaticComponent::PhysicsStaticComponent()
{
	LOGGER_TRACE("PhysicsStaticComponent constructor called");
	FixtureDefinition.density = 0.0f;
}

PhysicsStaticComponent::~PhysicsStaticComponent()
{
	LOGGER_TRACE("PhysicsStaticComponent destructor called");
	if (Body == nullptr)
		return;

	Body->DestroyFixture(Fixture);
	PhysicsWorld::World->DestroyBody(Body);
	Body = nullptr;
	Fixture = nullptr;
}

PhysicsDynamicComponent::PhysicsDynamicComponent()
{
	LOGGER_TRACE("PhysicsDynamicComponent constructor called");
	BodyDefinition.type = b2_dynamicBody;
	FixtureDefinition.density = 1.0f;
	FixtureDefinition.friction = 0.2f;
	FixtureDefinition.restitution = 0.3f;
}

PhysicsDynamicComponent::~PhysicsDynamicComponent()
{
	LOGGER_TRACE("PhysicsDynamicComponent destructor called");
	if (Body == nullptr)
		return;

	Body->DestroyFixture(Fixture);
	PhysicsWorld::World->DestroyBody(Body);
	Body = nullptr;
	Fixture = nullptr;
}

void PhysicsDynamicComponent::Update()
{
	b2Vec2 position = Body->GetPosition();
	Position = glm::vec2(position.x, position.y);
	Rotation = Body->GetAngle();
}