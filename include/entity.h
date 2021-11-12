#pragma once
#include <string>
#include <glm/glm.hpp>
#include "graphics.h"

class InputComponent;
class PhysicsComponent;

class Entity {
public:
	float speed;
	std::string name;
	glm::vec2 position;
	glm::vec2 size;
	glm::vec2 direction;
public:
	Entity(PhysicsComponent* physicsComponent, OpenGL::GraphicsComponent* graphicsComponent);
	void Advance();
	void Draw();
	void UpdatePhysics();
private:
	InputComponent* input;
	PhysicsComponent* physics;
	OpenGL::GraphicsComponent* graphics;
};