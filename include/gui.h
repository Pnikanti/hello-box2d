#pragma once
#include <imgui.h>

namespace OpenGL {
	class Gui {
	public:
		Gui();
		~Gui();
		void Begin();
		void End();
	private:
		ImGuiContext* Context;
	};

	class GuiContext {
	public:
		virtual void Update();
	};

	class DebugGuiContext : public GuiContext {
	public:
		DebugGuiContext();
		void Update() override;
	public:
		ImGuiWindowFlags wFlags;
		bool visible;
	};

	class ApplicationGuiContext : public GuiContext {
	public:
		ApplicationGuiContext();
		void Update() override;
	public:
		ImGuiWindowFlags wFlags;
		bool visible;
	};
}