#include "kepch.h"
#include "OrthographicCameraController.h"

#include "KineticEngine/Input/Input.h"
#include "KineticEngine/Core/KeyCodes.h"

namespace KE {

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio),
		m_Bounds({ -m_AspectRatio * m_ZoomLevel,m_AspectRatio * m_ZoomLevel,-m_ZoomLevel,m_ZoomLevel }),
		m_Camera(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top),
		m_EnableRotation(rotation) {

	}

	void OrthographicCameraController::OnUpdate(Timestep ts) {
		KE_PROFILE_FUNCTION();

		if (Input::IsKeyPressed(KE_KEY_A))
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
		if (Input::IsKeyPressed(KE_KEY_D))
			m_CameraPosition.x += m_CameraTranslationSpeed * ts;

		if (Input::IsKeyPressed(KE_KEY_S))
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts;
		if (Input::IsKeyPressed(KE_KEY_W))
			m_CameraPosition.y += m_CameraTranslationSpeed * ts;

		if (m_EnableRotation) {
			if (Input::IsKeyPressed(KE_KEY_Q))
				m_CameraRotation += m_CameraRotationSpeed * ts;
			if (Input::IsKeyPressed(KE_KEY_E))
				m_CameraRotation -= m_CameraRotationSpeed * ts;

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);

		m_CameraTranslationSpeed = m_ZoomLevel * 2.f;
	}

	void OrthographicCameraController::OnEvent(Event& e) {
		KE_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(KE_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(KE_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	void OrthographicCameraController::OnResize(float width, float height) {
		m_AspectRatio = width / height;
		CalculateView();
	}

	void OrthographicCameraController::CalculateView() {
		m_Bounds = { -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel,-m_ZoomLevel,m_ZoomLevel };
		m_Camera.SetProjection(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top);
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e) {
		KE_PROFILE_FUNCTION();

		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		CalculateView();
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e) {
		KE_PROFILE_FUNCTION();

		OnResize((float)e.GetWidth(), (float)e.GetHeight());
		CalculateView();
		return false;
	}

}