#include "app.h"
#include "log.h"

OpenGL::Gui* Application::Gui = nullptr;
OpenGL::GuiContext* Application::GuiContext = nullptr;

Application::Application() :
	Context(nullptr)
{
	Logger::Init("Hello-Box2D");
	Context = new OpenGL::Context(800, 600, "Application");
	Gui = new OpenGL::Gui();
	GuiContext = new OpenGL::GameGui();
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
	{;
		Context->RenderOneFrame();
	}
}

int main()
{
	auto x = Application();
	x.Start();

	return 0;
}