#include "Window.h"

#include <glad/glad.h>
#include "KineticEngine/Log.h"

namespace KE {
	static bool glfwInitialized = false;

	Window::Window(int width, int height, std::string title) {
		if (!glfwInitialized) {
			if (!glfwInit()) {
				KE_CORE_FATAL("GLFW Initialization Failed!");
			}
			glfwInitialized = true;
		}

		KE_CORE_INFO("Creating Window ({0}, {1})", width, height);
		m_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		if (!m_Window) {
			KE_CORE_FATAL("Window Creation Failed!");
			glfwTerminate();
		}

		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if (!status) {
			KE_CORE_FATAL("Failed to Load GLAD!");
		}
	}

	Window::~Window() {
		glfwTerminate();
	}

	void Window::onUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	Window* Window::create(int width, int height, std::string title) {
		return new Window(width, height, title);
	}
}