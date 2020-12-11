#include "GraphicsContext.h"

#include <glad/glad.h>

#include "KineticEngine/Core.h"

namespace KE {
	GraphicsContext::GraphicsContext(GLFWwindow* window)
		:m_WindowHandle(window) {
		KE_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	GraphicsContext::~GraphicsContext() {

	}

	void GraphicsContext::Init() {
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		KE_CORE_ASSERT(status, "Failed to initialize Glad!");
	}

	void GraphicsContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}