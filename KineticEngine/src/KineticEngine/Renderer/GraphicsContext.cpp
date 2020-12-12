#include "kepch.h"
#include "GraphicsContext.h"

#include <glad/glad.h>

#include "KineticEngine/Core.h"

namespace KE {
	GraphicsContext::GraphicsContext(GLFWwindow* window)
		:m_WindowHandle(window) {
		KE_CORE_ASSERT(m_WindowHandle, "Window handle is null!")
	}

	GraphicsContext::~GraphicsContext() {

	}

	void GraphicsContext::Init() {
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		KE_CORE_ASSERT(status, "Failed to initialize Glad!");

		KE_CORE_INFO("OpenGL Info:");
		KE_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		KE_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		KE_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void GraphicsContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}