#pragma once

#include <memory>

#include "Core.h"
#include "LayerStack.h"
#include "Window/Window.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

namespace KE {

	class KE_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

	private:
		static Application* s_Instance;
	};

	// To be defined in client
	Application* CreateApplication();

}