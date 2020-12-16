#pragma once

#include <KineticEngine.h>
#include <glm/glm.hpp>
#include <algorithm>

class Paddle {
public:
	Paddle(glm::vec2 pos);

	void Move(float steps);
	void OnUpdate(KE::Timestep ts);
	void OnRender();

	glm::vec2 GetPos() { return m_Pos; }
	glm::vec2 GetSize() { return m_Size; }

private:
	glm::vec2 m_Pos;
	glm::vec2 m_Size;
	float m_YVel = 0;
};