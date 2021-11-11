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
	static OpenGL::Gui* Gui;
	static OpenGL::GuiContext* GuiContext;
private:
	OpenGL::Context* Context;
};