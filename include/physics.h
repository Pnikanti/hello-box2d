#pragma once
#include <glm/glm.hpp>
#include <box2d/b2_world.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>

class Entity;

class PhysicsWorld {
public:
	PhysicsWorld();
	~PhysicsWorld();
	void Update();
public:
	static b2World* World;
private:
	int32 VelocityIterations;
	int32 PositionIterations;
};

class PhysicsComponent {
public:
	PhysicsComponent();
	void CreateEntity(glm::vec2 position, glm::vec2 size, float rotation);
	glm::vec2 GetPosition();
	glm::vec2 GetSize();
	float GetRotationRadians();
	float GetRotationDegrees();
	virtual void Update();
public:
	glm::vec2 Size;
	glm::vec2 Position;
	float Rotation;
	b2Body* Body;
	b2Fixture* Fixture;
	b2BodyDef BodyDefinition;
	b2PolygonShape Shape;
	b2FixtureDef FixtureDefinition;
};

class PhysicsStaticComponent : public PhysicsComponent {
public:
	PhysicsStaticComponent();
	~PhysicsStaticComponent();
};

class PhysicsDynamicComponent : public PhysicsComponent {
public:
	PhysicsDynamicComponent();
	~PhysicsDynamicComponent();
	void Update() override;
};