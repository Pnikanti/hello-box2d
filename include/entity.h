#pragma once
#include <string>
#include <glm/glm.hpp>
#include "graphics.h"

class InputComponent;
class PhysicsComponent;

class Entity {
public:
	Entity(PhysicsComponent* physicsComponent, OpenGL::GraphicsComponent* graphicsComponent);
	Entity(PhysicsComponent* physicsComponent, OpenGL::GraphicsComponent* graphicsComponent, glm::vec2 position, glm::vec2 size, float rotation);
	~Entity();
	void Advance();
	void Draw();
	glm::vec2 GetSize();
	glm::vec2 GetPosition();
	float GetRotationDegrees();
	float GetRotationRadians();
	void SetAttributes(glm::vec2 position, glm::vec2 size, float rotation);
private:
	InputComponent* input;
	PhysicsComponent* physics;
	OpenGL::GraphicsComponent* graphics;
};