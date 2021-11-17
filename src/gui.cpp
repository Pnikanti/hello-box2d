#include <glew/glew.h>
#include <glfw/glfw3.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "gui.h"
#include "entitymanager.h"
#include "entity.h"
#include "context.h"
#include "log.h"
#include "graphics.h"
#include "physics.h"

namespace OpenGL {
	Gui::Gui() 
		: Context(ImGui::CreateContext())
	{
		IMGUI_CHECKVERSION();
		ImGui::SetCurrentContext(Context);
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(Context::Window, true);
		ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));
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

	DebugGuiContext::DebugGuiContext() : wFlags(0), visible(true)
	{
		wFlags |= ImGuiWindowFlags_NoBackground;
		wFlags |= ImGuiWindowFlags_NoTitleBar;
		wFlags |= ImGuiWindowFlags_NoResize;
		wFlags |= ImGuiWindowFlags_NoMove;
		LOGGER_TRACE("WindowFlags: {0}", wFlags);
	}

	ApplicationGuiContext::ApplicationGuiContext() : wFlags(0), visible(true)
	{
		wFlags |= ImGuiWindowFlags_NoBackground;
		wFlags |= ImGuiWindowFlags_NoTitleBar;
		wFlags |= ImGuiWindowFlags_NoResize;
		wFlags |= ImGuiWindowFlags_NoMove;
		LOGGER_TRACE("WindowFlags: {0}", wFlags);
	}

	void DebugGuiContext::Update() {
		ImGui::SetNextWindowPos(ImVec2(0, 0)); // top-left
		ImGui::SetNextWindowSize(ImVec2(800, 200));
		ImGui::Begin("Debug", &visible, wFlags);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Text("Total Allocated (bytes): %u", Context::AllocatedMemory);
		ImGui::Text("Freed (bytes): %u", Context::FreedMemory);
		ImGui::Text("Current (bytes): %u", Context::AllocatedMemory - Context::FreedMemory);
		ImGui::Text("Entity vector size: %u", EntityManager::GetEntities().size());
		ImGui::End();
	}

	void ApplicationGuiContext::Update() {
		ImGui::SetNextWindowPos(ImVec2(Context::SCR_WIDTH - 100, 200)); // top-right
		ImGui::SetNextWindowSize(ImVec2(100, 200));
		ImGui::Begin("Application", &visible, wFlags);
		if (ImGui::Button("Spawn Box", ImVec2(75, 50)))
		{
			LOGGER_WARN("SPAWN PRESSED!");
			EntityManager::Get().CreateEntity(
				new PhysicsDynamicComponent(),
				new OpenGL::QuadComponent(),
				glm::vec2(0.0f, 10.0f),
				glm::vec2(0.5f, 0.5f),
				30.0f
			);

		}
		if (ImGui::Button("Delete Box", ImVec2(75, 50)))
		{
			LOGGER_WARN("DELETE PRESSED!");
			delete EntityManager::GetEntities().back();
			EntityManager::GetEntities().pop_back();
		}
		ImGui::End();
	}
}