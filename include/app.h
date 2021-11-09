#pragma once
#include "context.h"

class Application {
public:
	Application();
	~Application();
	void Start();
	void Loop();
private:
	OpenGL::Context* Context;
};