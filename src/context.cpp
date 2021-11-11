#include <glew/glew.h>
#include <glfw/glfw3.h>
#include "context.h"
#include "app.h"
#include "log.h"

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

	void Context::RenderOneFrame()
	{
		Alive = !glfwWindowShouldClose(Window);
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		GuiContext->Begin();
		Application::ApplicationGuiContext->Update();
		Application::DebugGuiContext->Update();
		GuiContext->End();
		glfwSwapBuffers(Window);
		glfwPollEvents();
	}
}