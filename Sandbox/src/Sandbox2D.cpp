#include "Sandbox2D.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp> 
#include <glm/gtc/random.hpp>

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"),
	m_CameraController(1280.0f / 720.0f, true) {

}

void Sandbox2D::OnAttach() {
	KE_PROFILE_FUNCTION();

	m_Texture = KE::Texture2D::Create("assets/textures/Container.png");
	m_Spritesheet = KE::Texture2D::Create("assets/textures/Spritesheet.png");

	m_TextureVortex = KE::SubTexture2D::CreateFromCoords(m_Spritesheet, { 11, 6 }, { 128, 128 });
	m_TextureDoor = KE::SubTexture2D::CreateFromCoords(m_Spritesheet, { 6, 0 }, { 128, 128 }, { 1, 2 });

	m_Particle.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	m_Particle.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_Particle.SizeBegin = 0.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 1.0f;
	m_Particle.Velocity = { 0.0f, 0.0f };
	m_Particle.VelocityVariation = { 3.0f, 1.0f };
	m_Particle.Position = { 0.0f, 0.0f };
}

void Sandbox2D::OnDetach() {
	KE_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(KE::Timestep ts) {
	KE_PROFILE_FUNCTION();

	m_Ts = ts;

	// Update
	m_CameraController.OnUpdate(ts);


	// Render
	{
		KE_PROFILE_SCOPE("Renderer Prep");
		KE::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.f });
		KE::RenderCommand::Clear();
	}

	KE::Renderer2D::ResetStats();
	{
		static float rotation = 0.f;
		rotation += ts * 1.f;

		KE_PROFILE_SCOPE("Renderer Draw");
		KE::Renderer2D::BeginScene(m_CameraController.GetCamera());
		KE::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.f });
		KE::Renderer2D::DrawQuad({ 1.0f, 0.8f }, { 1.0f, 1.0f }, m_SquareColor);
		KE::Renderer2D::DrawQuad({ -1.0f, -0.8f }, { 1.0f, 1.0f }, m_Texture, 10.f, { 0.6f, 1.0f, 0.8f , 1.f });
		KE::Renderer2D::DrawQuad({ 0.0f, 2.f }, { 1.0f, 2.0f }, m_TextureDoor);
		KE::Renderer2D::DrawRotatedQuad({ -1.0f, -0.8f }, { 0.4f, 0.4f }, rotation, m_SquareColor);
		KE::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f }, { 1.f, 1.f }, 1.f, m_TextureVortex);
		//KE::Renderer2D::EndScene();

		//KE::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -10.f; y < 10.f; y += 1.f) {
			for (float x = -10.f; x < 10.f; x += 1.f) {
				glm::vec4 color = { (x + 10.0f) / 20.f, 0.4f , (y + 10.0f) / 20.f, 0.5f };
				KE::Renderer2D::DrawQuad({ x, y, -0.05 }, { 0.2f, 0.2f }, color);
			}
		}
		KE::Renderer2D::EndScene();
	}

	if (KE::Input::IsMouseButtonPressed(KE_MOUSE_BUTTON_LEFT)) {
		auto [x, y] = KE::Input::GetMousePosition();
		auto width = KE::Application::Get().GetWindow().GetWidth();
		auto height = KE::Application::Get().GetWindow().GetHeight();

		auto bounds = m_CameraController.GetBounds();
		auto pos = m_CameraController.GetCamera().GetPosition();
		x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
		y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
		m_Particle.Position = { x + pos.x, y + pos.y };
		for (uint32_t i = 0; i < 50; i++)
			m_ParticleSystem.Emit(m_Particle);
	}
	//KE::RenderCommand::Clear();
	/*if (KE::Input::IsMouseButtonPressed(KE_MOUSE_BUTTON_LEFT)) {
		m_Particle.Position = { 0.f, 0.f };
		m_ParticleSystem.Emit(m_Particle);
	}*/
	m_ParticleSystem.OnUpdate(ts);
	m_ParticleSystem.OnRender(m_CameraController.GetCamera());
}

void Sandbox2D::OnImGuiRender() {
	KE_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	float fps = 1.f / m_Ts.GetSeconds();
	ImGui::Text(std::to_string(fps).c_str());

	auto stats = KE::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
	ImGui::End();
}

void Sandbox2D::OnEvent(KE::Event& e) {
	m_CameraController.OnEvent(e);
}
