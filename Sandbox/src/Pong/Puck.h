#pragma once

#include <KineticEngine.h>

#include <glm/glm.hpp>

#include "Paddle.h"

class Puck {
public:
	Puck();
	~Puck() = default;

	void Reset();
	void OnUpdate(KE::Timestep ts);
	void CheckEdges();
	void CheckPaddle(Paddle paddle);
	void OnRender();

private:
	float m_Size = 0.05f;
	float m_Speed = 2.f;
	glm::vec2 m_Pos;
	glm::vec2 m_Vel;
};