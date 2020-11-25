#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace KE {
	Application::Application() {
		m_Window = std::unique_ptr<Window>(Window::create(1280, 720, "Kinetic Engine!"));
	}

	Application::~Application() {

	}

	void Application::run() {
		WindowResizeEvent e(1280, 720);
		KE_TRACE(e);
		if (e.isInCategory(EventCategoryApplication))
		{
			KE_TRACE(e);
		}
		if (e.isInCategory(EventCategoryInput))
		{
			KE_TRACE(e);
		}

		while (m_Running) {
			m_Window->onUpdate();
		}
	}
}