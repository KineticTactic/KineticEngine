#pragma once

namespace KE {
	class Timestep {
	public:
		Timestep(float time = 0.f)
			:m_Time(time) {

		}

		float GetSeconds() const {
			return m_Time;
		}

		float GetMilliseconds() const {
			return m_Time * 1000.0f;
		}

		operator float() const {
			return m_Time;
		}

	private:
		float m_Time;
	};
}