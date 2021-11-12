#pragma once
#include <vector>
#include "context.h"
#include "gui.h"

class Entity;
class OrthographicCamera;

class Application {
public:
	Application();
	~Application();
	void Start();
	void Loop();
	void CreateDebugGui();
	void CreateApplicationGui();
	void CreateBox();
public:
	static std::vector<Entity*> Entities;
	static std::vector<OpenGL::GuiContext*> GuiContexts;
	static float MS_PER_UPDATE;
private:
	OpenGL::Context* Context;
	OrthographicCamera* Camera;
private:
	OrthographicCamera* CreateCamera(float width, float height);
};