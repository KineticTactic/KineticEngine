#include "Sandbox2D.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp> 

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"),
	m_CameraController(1280.0f / 720.0f, true) {

}

void Sandbox2D::OnAttach() {
	KE_PROFILE_FUNCTION();

	m_Texture = KE::Texture2D::Create("assets/textures/Container.png");
}

void Sandbox2D::OnDetach() {
	KE_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(KE::Timestep ts) {
	KE_PROFILE_FUNCTION();

	// Update
	m_CameraController.OnUpdate(ts);


	// Render
	{
		KE_PROFILE_SCOPE("Renderer Prep");
		KE::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		KE::RenderCommand::Clear();
	}

	{
		KE_PROFILE_SCOPE("Renderer Draw");
		KE::Renderer2D::BeginScene(m_CameraController.GetCamera());

		KE::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, m_SquareColor);
		KE::Renderer2D::DrawQuad({ 1.0f, 0.8f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.f });
		KE::Renderer2D::DrawQuad({ -1.0f, -0.8f }, { 1.0f, 1.0f }, m_Texture, 1.f, { 0.6f, 1.0f, 0.8f , 1.f });
		KE::Renderer2D::DrawRotatedQuad({ -1.0f, -0.8f }, { 0.4f, 0.4f }, 1.f, m_SquareColor);
		KE::Renderer2D::DrawRotatedQuad({ 1.0f, 0.8f }, { 1.f, 1.f }, 1.f, m_Texture);

		KE::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender() {
	KE_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(KE::Event& e) {
	m_CameraController.OnEvent(e);
}
