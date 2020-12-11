#pragma once

#include <GLFW/glfw3.h>

namespace KE {
	class GraphicsContext {
	public:
		GraphicsContext(GLFWwindow* window);
		~GraphicsContext();

		void Init();
		void SwapBuffers();

	private:
		GLFWwindow* m_WindowHandle;
	};
}