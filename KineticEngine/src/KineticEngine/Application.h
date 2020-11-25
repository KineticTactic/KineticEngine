#pragma once

#include <memory>

#include "Core.h"
#include "Window/Window.h"
#include "Events/Event.h"

namespace KE {

	class KE_API Application {
	public:
		Application();
		virtual ~Application();

		void run();

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To be defined in client
	Application* createApplication();

}