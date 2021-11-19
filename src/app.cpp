#include <glfw/glfw3.h>
#include <string.h>
#include <box2d/b2_body.h>
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

Application::Application(int width, int height) :
	Context(nullptr)
{
	Logger::Init("Hello-Box2D");
	EntityManager::Init(20);
	CreateDebugGui();
	CreateApplicationGui();
	Physics = new PhysicsWorld();
	Context = new OpenGL::Context(width, height, "Application");
	Context->AddShader(std::string("BasicShader"), std::string("res/shaders/vertex.shader"), std::string("res/shaders/fragment.shader"));
	Context->Start();
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
		0.0f,
		glm::vec3(255.0f, 255.0f, 0.0f),
		b2_staticBody,
		1.0f,
		1.0f,
		0.0f
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
			for (auto i = EntityManager::GetEntities().begin(); i != EntityManager::GetEntities().end(); i++)
			{
				if ((*i) != nullptr)
					(*i)->Advance();

				if ((*i)->Position.y < -50.0f)
				{
					delete (*i);
					(*i) = nullptr;
					EntityManager::GetEntities().erase(i--);
				}
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

int main()
{
	auto x = Application(1200, 800);
	x.Start();

	return 0;
}