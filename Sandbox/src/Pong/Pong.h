#pragma once

#include <KineticEngine.h>

#include "Paddle.h"
#include "Puck.h"

class Pong : public KE::Layer {
public:
	Pong();
	virtual ~Pong() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(KE::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(KE::Event& e) override;

private:
	KE::OrthographicCamera m_Camera;

	KE::Ref<KE::VertexArray> m_VertexArray;
	KE::Ref<KE::Shader> m_FlatColoShader;

	Paddle m_RightPaddle;
	Paddle m_LeftPaddle;
	Puck m_Puck;
};

