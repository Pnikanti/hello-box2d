#pragma once
#include <imgui.h>
#include <unordered_map>
#include <glm/glm.hpp>

namespace OpenGL { class Gui; }
struct GLFWwindow;
class OrthographicCamera;

namespace OpenGL {
	class Context {
	public:
		Context(int width, int height, const char* windowName);
		~Context();
		void RenderOneFrame();
		void AddShader(std::string& shaderName, std::string& vertexShader, std::string& fragmentShader);
		void UpdateViewProjectionMatrix(OrthographicCamera* camera);
		void UpdateUniformResolution();
	public:
		static GLFWwindow* Window;
		bool Alive;
		static unsigned int SCR_WIDTH;
		static unsigned int SCR_HEIGHT;
		static unsigned int AllocatedMemory;
		static unsigned int FreedMemory;
		static std::unordered_map<std::string, unsigned int> Shaders;
	private:
		static void FrameBufferSizeCb(GLFWwindow* window, int width, int height);
		void RenderGui();
		void UpdateAllRenderTargets();
	private:
		static Gui* GuiContext;
		glm::mat4 viewProjectionMatrix;
	};
}