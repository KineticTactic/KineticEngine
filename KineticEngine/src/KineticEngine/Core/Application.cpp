#include "kepch.h"
#include "Application.h"

#include "KineticEngine/Renderer/Renderer.h"
#include "KineticEngine/Input/Input.h"
#include "KineticEngine/Core/Timestep.h"

namespace KE {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application(const std::string& name) {
		KE_PROFILE_FUNCTION();

		KE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create(1280, 720, name));
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer;
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application() {

	}

	void Application::OnEvent(Event& e) {
		KE_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

		//KE_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer) {
		KE_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer) {
		KE_PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::Close() {
		m_Running = false;
	}

	void Application::Run() {
		KE_PROFILE_FUNCTION();

		while (m_Running) {
			KE_PROFILE_SCOPE("RunLoop");

			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized) {
				{
					KE_PROFILE_SCOPE("LayerStack Updates");
					for (Layer* layer : m_LayerStack)
						layer->OnUpdate(timestep);
				}
			}

			{
				KE_PROFILE_SCOPE("LayerStack OnImGuiRender");
				m_ImGuiLayer->Begin();
				for (Layer* layer : m_LayerStack)
					layer->OnImGuiRender();
				m_ImGuiLayer->End();
			}


			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e) {
		KE_PROFILE_FUNCTION();

		if (e.GetWidth() == 0 || e.GetHeight() == 0) {
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return true;
	}
}