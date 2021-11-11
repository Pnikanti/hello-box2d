#include "app.h"
#include "log.h"

OpenGL::GuiContext* Application::DebugGuiContext = nullptr;
OpenGL::GuiContext* Application::ApplicationGuiContext = nullptr;

Application::Application() :
	Context(nullptr)
{
	Logger::Init("Hello-Box2D");
	Context = new OpenGL::Context(800, 600, "Application");
	DebugGuiContext = new OpenGL::DebugGuiContext();
	ApplicationGuiContext = new OpenGL::ApplicationGuiContext();
}

Application::~Application()
{

}

void Application::Start()
{
	Loop();
}

void Application::Loop()
{
	while (Context->Alive)
	{
		Context->RenderOneFrame();
	}
}

int main()
{
	auto x = Application();
	x.Start();

	return 0;
}