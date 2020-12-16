#include "Paddle.h"

Paddle::Paddle(glm::vec2 pos)
	: m_Pos(pos),
	m_Size(0.1f, 0.5f) {

}

void Paddle::Move(float steps) {
	m_YVel += steps;
}

void Paddle::OnUpdate(KE::Timestep ts) {
	m_Pos.y += m_YVel * ts;
	m_YVel = 0;
	m_Pos.y = std::clamp(m_Pos.y, m_Size.y / 2.f - 1.f, 1.f - m_Size.y / 2.f);
}

void Paddle::OnRender() {
	KE::Renderer2D::DrawQuad(m_Pos, m_Size, { 1.f, 1.f, 1.f, 1.f });
}