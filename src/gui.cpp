#include "gui.h"
#include "context.h"
#include "log.h"
#include <glew/glew.h>
#include <glfw/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace OpenGL {
	Gui::Gui() {
		IMGUI_CHECKVERSION();
		Context = ImGui::CreateContext();
		ImGui::SetCurrentContext(Context);

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(Context::Window, true);
		ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));

		// ImGui settings
		ImGuiWindowFlags windowFlags = 0;
		windowFlags |= ImGuiWindowFlags_NoBackground;
		windowFlags |= ImGuiWindowFlags_NoTitleBar;
		LOGGER_TRACE("WindowFlags: {0}", windowFlags);
	}

	Gui::~Gui() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void Gui::Begin() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void Gui::End() {
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void GuiContext::Update() {}

	void GameGui::Update() {
		ImGui::Begin("Hello World!");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}
}