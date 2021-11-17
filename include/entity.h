#pragma once
#include <string>
#include <glm/glm.hpp>
#include "graphics.h"

class InputComponent;
class PhysicsComponent;

class Entity {
public:
	Entity();
	Entity(PhysicsComponent* physicsComponent, OpenGL::GraphicsComponent* graphicsComponent);
	void Advance();
	void Draw();
	glm::vec2 GetSize();
	glm::vec2 GetPosition();
	float GetRotationDegrees();
	float GetRotationRadians();
	void SetAttributes(glm::vec2 position, glm::vec2 size, float rotation);
public:
	bool exists;
private:
	InputComponent* input;
	PhysicsComponent* physics;
	OpenGL::GraphicsComponent* graphics;
};