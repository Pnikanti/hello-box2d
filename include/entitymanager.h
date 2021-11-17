#pragma once

#include <memory>
#include <vector>
#include "entity.h"

class PhysicsComponent;
namespace OpenGL { class GraphicsComponent; }

class EntityManager {
public:
	EntityManager(const EntityManager&) = delete; // copy-constructor
	void CreateEntity(PhysicsComponent* physics, OpenGL::GraphicsComponent* graphics);
	void CreateEntity(PhysicsComponent* physics, OpenGL::GraphicsComponent* graphics, glm::vec2 size, glm::vec2 position, float rotation);
	static EntityManager& Get() { 
		static EntityManager Instance; 
		return Instance; 
	}
	static std::vector<Entity>& GetEntities() { return EntityManager::Get().Entities; }
protected:
	EntityManager::EntityManager() = default; // constructor
private:
	static std::vector<Entity> Entities;
};