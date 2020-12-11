#include "Window.h"

#include <glad/glad.h>

#include "KineticEngine/Log.h"
#include "KineticEngine/Events/ApplicationEvent.h"
#include "KineticEngine/Events/KeyEvent.h"
#include "KineticEngine/Events/MouseEvent.h"

namespace KE {
	static bool glfwInitialized = false;

	static void GLFWErrorCallback(int error, const char* description) {
		KE_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window::Window(int width, int height, std::string title) {
		m_Data.Width = width;
		m_Data.Height = height;

		if (!glfwInitialized) {
			if (!glfwInit()) {
				KE_CORE_FATAL("GLFW Initialization Failed!");
			}
			glfwSetErrorCallback(GLFWErrorCallback);
			glfwInitialized = true;
		}

		KE_CORE_INFO("Creating Window ({0}, {1})", width, height);
		m_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		if (!m_Window) {
			KE_CORE_FATAL("Window Creation Failed!");
			glfwTerminate();
		}

		m_Context = new GraphicsContext(m_Window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		// Set GLFW callbacks

		// Window Resize
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
			});

		// Window Close
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
			});

		// Key Callback
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
			case GLFW_PRESS: {
				KeyPressedEvent event(key, 0);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE: {
				KeyReleasedEvent event(key);
				data.EventCallback(event);
				break;
			}
			case GLFW_REPEAT: {
				KeyPressedEvent event(key, 1);
				data.EventCallback(event);
				break;
			}
			}
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent event(keycode);
			data.EventCallback(event);
			});

		// Mouse Callbacks
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
			case GLFW_PRESS: {
				MouseButtonPressedEvent event(button);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE: {
				MouseButtonReleasedEvent event(button);
				data.EventCallback(event);
				break;
			}
			}
			});

		// Scroll
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
			});

		// MousePos
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
			});
	}

	Window::~Window() {
		glfwTerminate();
	}

	void Window::OnUpdate() {
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	Window* Window::Create(int width, int height, std::string title) {
		return new Window(width, height, title);
	}

	void Window::SetEventCallback(const EventCallbackFn& callback) {
		m_Data.EventCallback = callback;
	}
}