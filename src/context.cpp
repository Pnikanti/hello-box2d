#include <glew/glew.h>
#include <glfw/glfw3.h>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "context.h"
#include "gui.h"
#include "camera.h"
#include "app.h"
#include "log.h"
#include "shader.h"
#include "entity.h"
#include "entitymanager.h"

void* operator new(size_t size)
{
	OpenGL::Context::AllocatedMemory += size;
	return malloc(size);
}

void operator delete(void* memory, size_t size)
{
	OpenGL::Context::FreedMemory += size;
	free(memory);
}

namespace OpenGL {
	unsigned int Context::AllocatedMemory = 0;
	unsigned int Context::FreedMemory = 0;
	unsigned int Context::SCR_WIDTH = 800;
	unsigned int Context::SCR_HEIGHT = 600;
	GLFWwindow* Context::Window = nullptr;
	Gui* Context::GuiContext = nullptr;
	std::unordered_map<std::string, unsigned int> Context::Shaders = std::unordered_map<std::string, unsigned int>();

	Context::Context(int width, int height, const char* windowName)
		: Alive(1)
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		Window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, windowName, NULL, NULL);

		if (!Window)
		{
			glfwTerminate();
		}

		glfwMakeContextCurrent(Window);
		glfwSetFramebufferSizeCallback(Window, FrameBufferSizeCb);
		GLenum glewInitialized = glewInit();

		if (glewInitialized == GLEW_OK)
		{
			LOGGER_INFO("Glew version: {0}", glewGetString(GLEW_VERSION));
		}
		else
		{
			LOGGER_ERROR("Glew error: {0}", glewGetErrorString(glewInitialized));
		}

		glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
		glfwSwapInterval(1); // Enable vsync
		GuiContext = new Gui();
		LOGGER_INFO("Context initialized!");
	}

	Context::~Context()
	{
		ImGui::DestroyContext();
		glfwTerminate();
	}

	void Context::FrameBufferSizeCb(GLFWwindow* window, int width, int height)
	{
		SCR_WIDTH = width;
		SCR_HEIGHT = height;
		glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	}

	void Context::RenderGui()
	{
		GuiContext->Begin();
		for (auto i : Application::GuiContexts)
		{
			if (i != nullptr)
			{
				i->Update();
			}
		}
		GuiContext->End();
	}

	void Context::AddShader(std::string& shaderName, std::string& vertexShader, std::string& fragmentShader)
	{
		LOGGER_INFO("Using shaders: {0}, {1}", vertexShader, fragmentShader);
		ShaderHandler::ShaderProgramSource source = ShaderHandler::Parse(vertexShader, fragmentShader);
		Shaders[shaderName] = ShaderHandler::Create(source.VertexSource, source.FragmentSource);
	}

	void Context::UpdateUniformResolution()
	{
		glm::vec2 resolution = glm::vec2(SCR_WIDTH, SCR_HEIGHT);

		for (auto i : Shaders)
		{
			glUseProgram(i.second);
			unsigned int resolutionUniform = glGetUniformLocation(i.second, "resolution");
			if (resolutionUniform)
			{
				LOGGER_TRACE("Setting resolution: {0} to resolutionUniform", glm::to_string(resolution));
				glUniform2fv(resolutionUniform, 1, glm::value_ptr(resolution));
			}
		}
	}

	void Context::UpdateViewProjectionMatrix(OrthographicCamera* camera)
	{
		LOGGER_TRACE("Updating viewProjectionmatrix: {0}", glm::to_string(camera->viewProjectionMatrix));
		viewProjectionMatrix = camera->viewProjectionMatrix;

		for (auto i : Shaders)
		{
			glUseProgram(i.second);
			unsigned int viewProjectionUniform = glGetUniformLocation(i.second, "viewProjection");
			glUniformMatrix4fv(viewProjectionUniform, 1, GL_FALSE, glm::value_ptr(viewProjectionMatrix));
		}
	}

	void Context::UpdateAllRenderTargets()
	{
		for (auto i : EntityManager::GetEntities())
		{
			if (i != nullptr)
				i->Draw();
		}
	}

	void Context::RenderOneFrame()
	{
		Alive = !glfwWindowShouldClose(Window);
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		RenderGui();
		UpdateAllRenderTargets();
		glfwSwapBuffers(Window);
		glfwPollEvents();
	}
}