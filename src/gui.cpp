#include <glew/glew.h>
#include <glfw/glfw3.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <box2d/b2_body.h>
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

	ApplicationGuiContext::ApplicationGuiContext() : wFlags(0), wBackgroundFlags(0), visible(true)
	{
		wFlags |= ImGuiWindowFlags_NoBackground;
		wFlags |= ImGuiWindowFlags_NoTitleBar;
		wFlags |= ImGuiWindowFlags_NoResize;
		wFlags |= ImGuiWindowFlags_NoMove;
		wBackgroundFlags |= ImGuiWindowFlags_NoTitleBar;
		wBackgroundFlags |= ImGuiWindowFlags_NoResize;
		wBackgroundFlags |= ImGuiWindowFlags_NoMove;
		LOGGER_TRACE("WindowFlags: {0}", wFlags);
		LOGGER_TRACE("WindowBackgroundFlags: {0}", wBackgroundFlags);

	}

	void DebugGuiContext::Update() {
		ImGui::SetNextWindowPos(ImVec2((int)Context::SCR_WIDTH - 350, 0)); // top-left
		ImGui::SetNextWindowSize(ImVec2(350, 200));
		ImGui::Begin("Debug", &visible, wFlags);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Text("Total Allocated (bytes): %u", Context::AllocatedMemory);
		ImGui::Text("Freed (bytes): %u", Context::FreedMemory);
		ImGui::Text("Current (bytes): %u", Context::AllocatedMemory - Context::FreedMemory);
		ImGui::Text("Entity vector size: %u", EntityManager::GetEntities().size());
		ImGui::End();
	}

	void ApplicationGuiContext::Update() {

		// Background
		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::SetNextWindowSize(ImVec2(325, (int)Context::SCR_HEIGHT));
		ImGui::Begin("Background", &visible, wBackgroundFlags);
		ImGui::End();

		// Color picker
		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::SetNextWindowSize(ImVec2(300, 300));
		ImGui::Begin("Color", &visible, wFlags);
		LOGGER_INFO("Color Picker: r: {0} g: {1}, b: {2}", fCurrentColor[0], fCurrentColor[1], fCurrentColor[2]);
		ImGui::ColorPicker3("Color Picker", &fCurrentColor[0], 0);
		ImGui::End();

		// Sliders
		ImGui::SetNextWindowPos(ImVec2(0, 300));
		ImGui::SetNextWindowSize(ImVec2(300, 200));
		ImGui::Begin("Sliders", &visible, wFlags);
		ImGui::SliderFloat("Size", &fSize, 0.1f, 5.0f);
		ImGui::SliderFloat("Density", &fDensity, 0.0f, 1.0f);
		ImGui::SliderFloat("Friction", &fFriction, 0.0f, 1.0f);
		ImGui::SliderFloat("Restitution", &fRestitution, 0.0f, 1.0f);
		ImGui::SliderFloat("Rotation", &fRotation, 0.0f, 360.0f);
		ImGui::End();

		// Spawn controls
		ImGui::SetNextWindowPos(ImVec2(0, 500)); 
		ImGui::SetNextWindowSize(ImVec2(300, 200));
		ImGui::Begin("Control Panel", &visible, wFlags);
		if (ImGui::Button("Spawn Box", ImVec2(75, 50)))
		{
			LOGGER_WARN("SPAWN PRESSED!");
			EntityManager::Get().CreateEntity(
				new PhysicsDynamicComponent(),
				new OpenGL::QuadComponent(),
				glm::vec2(fSize),
				glm::vec2(0.0f, 10.0f),
				fRotation,
				glm::vec3((float)fCurrentColor[0], (float)fCurrentColor[1], (float)fCurrentColor[2]),
				b2_dynamicBody,
				fDensity,
				fFriction,
				fRestitution
			);

		}
		ImGui::SameLine();
		if (ImGui::Button("Delete Box", ImVec2(75, 50)))
		{
			LOGGER_WARN("DELETE PRESSED!");

			// hack to not cause crash and to not delete static ground
			if (EntityManager::GetEntities().size() > 1)
			{
				delete EntityManager::GetEntities().back();
				EntityManager::GetEntities().pop_back();
			}
		}
		ImGui::End();
	}
}