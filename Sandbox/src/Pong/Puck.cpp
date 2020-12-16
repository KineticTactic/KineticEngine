#include "Puck.h"

#include <glm/gtx/rotate_vector.hpp>
#include <cmath>

static float lerp(float a, float b, float f) {
	return (a * (1.0 - f)) + (b * f);
}

Puck::Puck()
	: m_Pos(0.f, 0.f),
	m_Vel(m_Speed, 0.f) {

}

void Puck::Reset() {
	m_Pos.x = 0.f;
	m_Pos.y = 0.f;
}

void Puck::OnUpdate(KE::Timestep ts) {
	m_Pos += (m_Vel * ts.GetSeconds());
}

void Puck::CheckEdges() {
	if (m_Pos.y <= -1.f + m_Size || m_Pos.y >= 1.f - m_Size) {
		m_Vel.y = -m_Vel.y;
	}
	//if (m_Pos.x <= 0) {
	//	// Right score ++
	//	Reset();
	//}
	//if (m_Pos.x >= width) {
	//	// Left score ++
	//	Reset();
	//}
}

void Puck::CheckPaddle(Paddle paddle) {
	glm::vec2 paddlePos = paddle.GetPos();
	glm::vec2 paddleSize = paddle.GetSize();

	if (paddlePos.x > 0) {
		if (m_Pos.x + m_Size / 2.f >= paddlePos.x - paddleSize.x / 2.f) {
			if ((m_Pos.y - m_Size / 2.f < paddlePos.y + paddleSize.y / 2.f) &&
				(m_Pos.y + m_Size / 2.f > paddlePos.y - paddleSize.y / 2.f)) {
				m_Pos.x = paddlePos.x - paddleSize.x / 2.f - m_Size / 2.f;
				float yDiff = m_Pos.y - paddlePos.y;
				float angle = yDiff / (paddleSize.y / 2.f) * glm::radians(-45.f);
				m_Vel.x *= -1;
				m_Vel.y = 0;
				m_Vel = glm::rotate(m_Vel, angle);
				m_Vel = glm::normalize(m_Vel) * m_Speed;
			}
		}
	}
	else if (paddlePos.x < 0) {
		if (m_Pos.x - m_Size / 2.f <= paddlePos.x + paddleSize.x / 2.f) {
			if ((m_Pos.y - m_Size / 2.f < paddlePos.y + paddleSize.y / 2.f) &&
				(m_Pos.y + m_Size / 2.f > paddlePos.y - paddleSize.y / 2.f)) {
				m_Pos.x = paddlePos.x + paddleSize.x / 2.f + m_Size / 2.f;
				float yDiff = m_Pos.y - paddlePos.y;
				float angle = yDiff / (paddleSize.y / 2.f) * glm::radians(45.f);
				m_Vel.x *= -1;
				m_Vel.y = 0;
				m_Vel = glm::rotate(m_Vel, angle);
				m_Vel = glm::normalize(m_Vel) * m_Speed;
			}
		}
	}
}

void Puck::OnRender() {
	KE::Renderer2D::DrawQuad(m_Pos, { m_Size, m_Size }, { 0.f, 0.5f, 1.f, 1.f });
}