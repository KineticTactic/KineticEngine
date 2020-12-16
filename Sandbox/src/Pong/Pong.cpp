#include "Pong.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

Pong::Pong()
	:Layer("Sandbox2D"),
	m_Camera(-(1280.f / 720.f), (1280.f / 720.f), -1.f, 1.f),
	m_RightPaddle({ 1.65f, 0.f }),
	m_LeftPaddle({ -1.65f, 0.f }) {

}

void Pong::OnAttach() {

}

void Pong::OnDetach() {

}

void Pong::OnUpdate(KE::Timestep ts) {
	// Input
	static float moveSpeed = 2.f;
	if (KE::Input::IsKeyPressed(KE_KEY_UP)) {
		m_RightPaddle.Move(moveSpeed);
	}
	if (KE::Input::IsKeyPressed(KE_KEY_DOWN)) {
		m_RightPaddle.Move(-moveSpeed);
	}

	if (KE::Input::IsKeyPressed(KE_KEY_W)) {
		m_LeftPaddle.Move(moveSpeed);
	}
	if (KE::Input::IsKeyPressed(KE_KEY_S)) {
		m_LeftPaddle.Move(-moveSpeed);
	}

	// Update
	m_RightPaddle.OnUpdate(ts);
	m_LeftPaddle.OnUpdate(ts);
	m_Puck.OnUpdate(ts);
	m_Puck.CheckEdges();
	m_Puck.CheckPaddle(m_RightPaddle);
	m_Puck.CheckPaddle(m_LeftPaddle);

	// Render
	KE::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	KE::RenderCommand::Clear();

	KE::Renderer2D::BeginScene(m_Camera);

	m_RightPaddle.OnRender();
	m_LeftPaddle.OnRender();
	m_Puck.OnRender();

	KE::Renderer2D::EndScene();
}

void Pong::OnImGuiRender() {
}

void Pong::OnEvent(KE::Event& e) {
}
