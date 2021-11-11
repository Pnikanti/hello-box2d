#pragma once

struct ImGuiContext;

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

	class GameGui : public GuiContext {
	public:
		void Update() override;
	};
}