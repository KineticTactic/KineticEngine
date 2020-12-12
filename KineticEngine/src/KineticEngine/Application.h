#pragma once

#include "KineticEngine/Core.h"
#include "KineticEngine/LayerStack.h"
#include "KineticEngine/Window/Window.h"
#include "KineticEngine/Events/Event.h"
#include "KineticEngine/Events/ApplicationEvent.h"

#include "KineticEngine/Renderer/Shader.h"
#include "KineticEngine/Renderer/Buffer.h"
#include "KineticEngine/Renderer/VertexArray.h"
#include "KineticEngine/Renderer/OrthographicCamera.h"


#include "ImGui/ImGuiLayer.h"

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
		ImGuiLayer* m_ImGuiLayer;

		bool m_Running = true;
		LayerStack m_LayerStack;

		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		std::shared_ptr<Shader> m_Shader;

		OrthographicCamera m_Camera;

	private:
		static Application* s_Instance;
	};

	// To be defined in client
	Application* CreateApplication();

}