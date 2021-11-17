#include <glfw/glfw3.h>
#include <string.h>
#include "context.h"
#include "gui.h"
#include "app.h"
#include "log.h"
#include "camera.h"
#include "graphics.h"
#include "physics.h"
#include "entity.h"
#include "entitymanager.h"

std::vector<OpenGL::GuiContext*> Application::GuiContexts(std::vector<OpenGL::GuiContext*>(2));
float Application::TimeStep = 1.0f / 60.0f;

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
	Physics = new PhysicsWorld();
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
	EntityManager::Get().CreateEntity(
		new PhysicsStaticComponent(),
		new OpenGL::QuadComponent(),
		glm::vec2(10.0f, 0.25f),
		glm::vec2(0.0f, -10.0f),
		0.0f
	);

	EntityManager::Get().CreateEntity(
		new PhysicsDynamicComponent(),
		new OpenGL::QuadComponent(),
		glm::vec2(0.5f, 0.5f),
		glm::vec2(0.0f, 10.0f),
		30.0f
	);

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

		while (lag >= TimeStep)
		{
			Physics->Update();
			for (auto i : EntityManager::GetEntities())
			{
				if (i.exists)
					i.Advance();
			}
			lag -= TimeStep;
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
	float cameraDimensions = 20.0f;
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

int main()
{
	auto x = Application();
	x.Start();

	return 0;
}