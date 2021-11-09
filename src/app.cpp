#include "app.h"
#include "log.h"

Application::Application() :
	Context(nullptr)
{
	Logger::Init("Hello-Box2D");
	Context = new OpenGL::Context(800, 600, "Application");
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