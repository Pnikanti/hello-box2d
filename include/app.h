#pragma once
#include <vector>
#include "context.h"
#include "gui.h"

class Application {
public:
	Application();
	~Application();
	void Start();
	void Loop();
public:
	static OpenGL::GuiContext* DebugGuiContext;
	static OpenGL::GuiContext* ApplicationGuiContext;
private:
	OpenGL::Context* Context;
};