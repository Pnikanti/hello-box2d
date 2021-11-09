#pragma once
#include "imgui.h"

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
		bool Alive;
	private:
		static void FrameBufferSizeCb(GLFWwindow* window, int width, int height);
	};
}