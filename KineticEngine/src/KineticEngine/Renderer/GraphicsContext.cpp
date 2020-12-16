#include "kepch.h"
#include "GraphicsContext.h"

#include <glad/glad.h>

#include "KineticEngine/Core/Core.h"

namespace KE {
	GraphicsContext::GraphicsContext(GLFWwindow* window)
		:m_WindowHandle(window) {
		KE_CORE_ASSERT(m_WindowHandle, "Window handle is null!")
	}

	GraphicsContext::~GraphicsContext() {

	}

	void GraphicsContext::Init() {
		KE_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		KE_CORE_ASSERT(status, "Failed to initialize Glad!");

		KE_CORE_INFO("OpenGL Info:");
		KE_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		KE_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		KE_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

		int versionMajor, versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

		KE_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Kinetic Engine requires at least OpenGL version 4.5");
	}

	void GraphicsContext::SwapBuffers() {
		KE_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}
}