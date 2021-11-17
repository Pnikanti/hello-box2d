#pragma once
#include <vector>

namespace OpenGL { class GuiContext; class Context; }
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
public:
	static std::vector<OpenGL::GuiContext*> GuiContexts;
	static float TimeStep;
private:
	OpenGL::Context* Context;
	OrthographicCamera* Camera;
	PhysicsWorld* Physics;
private:
	OrthographicCamera* CreateCamera(float width, float height);
};