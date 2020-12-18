#pragma once

#include <KineticEngine.h>

#include "ParticleSystem.h"

class Sandbox2D : public KE::Layer {
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(KE::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(KE::Event& e) override;

private:
	KE::OrthographicCameraController m_CameraController;

	KE::Ref<KE::VertexArray> m_VertexArray;
	KE::Ref<KE::Shader> m_FlatColoShader;

	glm::vec4 m_SquareColor = { 0.f, 0.5f, 1.f, 1.f };
	KE::Ref<KE::Texture2D> m_Texture;

	KE::Timestep m_Ts;

	ParticleSystem m_ParticleSystem;
	ParticleProps m_Particle;
};

