#include <glew/glew.h>
#include <glfw/glfw3.h>
#include "context.h"
#include "app.h"
#include "log.h"


namespace OpenGL {
	GLFWwindow* Context::Window = nullptr;
	unsigned int Context::SCR_WIDTH = 800;
	unsigned int Context::SCR_HEIGHT = 600;

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
		Application::Gui->Begin();
		Application::GuiContext->Update();
		Application::Gui->End();
		glfwSwapBuffers(Window);
		glfwPollEvents();
	}
}