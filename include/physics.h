#pragma once
#include <box2d/b2_world.h>

class Entity;

class PhysicsComponent {
public:
	PhysicsComponent();
	~PhysicsComponent();
	void Update(Entity& entity);
private:
	b2World* PhysicsWorld;
};
