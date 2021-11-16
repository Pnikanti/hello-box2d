#pragma once
#include <vector>
#include "context.h"
#include "gui.h"

class Entity;
class OrthographicCamera;
class PhysicsWorld;

class Application {
public:
	Application();
	~Application();
	void Start();
	void Loop();
	void CreateDebugGui();
	void CreateApplicationGui();
	void CreateBox();
	void CreateGround();
public:
	static std::vector<Entity*> Entities;
	static std::vector<OpenGL::GuiContext*> GuiContexts;
	static float TimeStep;
private:
	OpenGL::Context* Context;
	OrthographicCamera* Camera;
	PhysicsWorld* Physics;
private:
	OrthographicCamera* CreateCamera(float width, float height);
};