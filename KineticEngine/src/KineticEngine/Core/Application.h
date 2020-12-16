#pragma once

#include "KineticEngine/Core/Core.h"

#include "KineticEngine/Core/LayerStack.h"
#include "KineticEngine/Window/Window.h"
#include "KineticEngine/Events/Event.h"
#include "KineticEngine/Events/ApplicationEvent.h"

#include "KineticEngine/Renderer/Shader.h"
#include "KineticEngine/Renderer/Buffer.h"
#include "KineticEngine/Renderer/VertexArray.h"
#include "KineticEngine/Renderer/OrthographicCamera.h"


#include "KineticEngine/ImGui/ImGuiLayer.h"

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
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;

		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;

		float m_LastFrameTime = 0.f;

	private:
		static Application* s_Instance;
	};

	// To be defined in client
	Application* CreateApplication();

}