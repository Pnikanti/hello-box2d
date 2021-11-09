#include <glew/glew.h>
#include <glfw/glfw3.h>
#include "context.h"
#include "log.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

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

		ImGuiContext* ImContext = ImGui::CreateContext();
		ImGui::SetCurrentContext(ImContext);
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(Window, true);
		ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));
	}

	Context::~Context()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
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

		ImGuiIO io = ImGui::GetIO(); (void)io;
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
		float r = 0.0f;
		float increment = 0.05f;
		static float f = 0.0f;
		static int counter = 0;
		bool demoWindow = true;
		bool anotherWindow = false;
		ImGui::Text("Hello ImGui!");
		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
		ImGui::Checkbox("Demo Window", &demoWindow);
		ImGui::Checkbox("Another Window", &anotherWindow);
		if (ImGui::Button("button"))
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(Window);
		glfwPollEvents();
	}
}