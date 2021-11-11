#pragma once
#include <imgui.h>
#include "gui.h"

struct GLFWwindow;

namespace OpenGL {
	class Context {
	public:
		Context(int width, int height, const char* windowName);
		~Context();
		void RenderOneFrame();
	public:
		static GLFWwindow* Window;
		static unsigned int SCR_WIDTH;
		static unsigned int SCR_HEIGHT;
		static unsigned int AllocatedMemory;
		static unsigned int FreedMemory;
		bool Alive;
	private:
		static void FrameBufferSizeCb(GLFWwindow* window, int width, int height);
	private:
		static Gui* GuiContext;
	};
}