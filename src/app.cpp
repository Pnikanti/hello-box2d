#include <glfw/glfw3.h>
#include <string.h>
#include "app.h"
#include "log.h"
#include "camera.h"
#include "graphics.h"
#include "physics.h"
#include "entity.h"

std::vector<Entity*> Application::Entities(std::vector<Entity*>(10));
std::vector<OpenGL::GuiContext*> Application::GuiContexts(std::vector<OpenGL::GuiContext*>(2));
float Application::MS_PER_UPDATE = 0.033; // 0.033 = 30x, 0.02 = 50x, 0.0166 = 60x per second

Application::Application() :
	Context(nullptr)
{
	Logger::Init("Hello-Box2D");
	Context = new OpenGL::Context(800, 600, "Application");
	CreateDebugGui();
	CreateApplicationGui();
	Context->AddShader(std::string("BasicShader"), std::string("res/shaders/vertex.shader"), std::string("res/shaders/fragment.shader"));
	Camera = CreateCamera(800, 600);
	Context->UpdateViewProjectionMatrix(Camera);
	Context->UpdateUniformResolution();
}

Application::~Application()
{
	for (auto i : GuiContexts)
	{
		if (i != nullptr)
		{
			delete i;
		}
	}
	GuiContexts.clear();
}

void Application::Start()
{
	CreateBox();
	Loop();
}

void Application::Loop()
{
	double previous, current, elapsed, lag;
	previous = current = elapsed = lag = 0.0;

	while (Context->Alive)
	{
		current = glfwGetTime();
		elapsed = current - previous;
		previous = current;
		lag += elapsed;

		while (lag >= MS_PER_UPDATE)
		{
			LOGGER_INFO("Advancing!");
			lag -= MS_PER_UPDATE;
		}
		Context->RenderOneFrame();
	}
}

void Application::CreateDebugGui()
{
	OpenGL::GuiContext* t = new OpenGL::DebugGuiContext();
	GuiContexts.push_back(t);
}

void Application::CreateApplicationGui()
{
	OpenGL::GuiContext* t = new OpenGL::ApplicationGuiContext();
	GuiContexts.push_back(t);

}

OrthographicCamera* Application::CreateCamera(float width, float height)
{
	float aspectRatio = width / height;
	float cameraDimensions = 8.0f;
	float bottom = -cameraDimensions;
	float top = cameraDimensions;
	float left = bottom * aspectRatio;
	float right = top * aspectRatio;

	LOGGER_TRACE("aspectRatio: {0}", aspectRatio);
	LOGGER_TRACE("bottom: {0}", bottom);
	LOGGER_TRACE("top: {0}", top);
	LOGGER_TRACE("left: {0}", left);
	LOGGER_TRACE("right: {0}", right);

	return new OrthographicCamera(left, right, bottom, top);
}

void Application::CreateBox()
{
	Entity* e = new Entity(
		new PhysicsComponent(),
		new OpenGL::QuadComponent()
	);
	Entities.push_back(e);
	
}

int main()
{
	auto x = Application();
	x.Start();

	return 0;
}