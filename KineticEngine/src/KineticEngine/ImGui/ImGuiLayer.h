#pragma once

#include "KineticEngine/Core/Layer.h"
#include "KineticEngine/Events/KeyEvent.h"
#include "KineticEngine/Events/MouseEvent.h"
#include "KineticEngine/Events/ApplicationEvent.h"

namespace KE {
	class KE_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }

	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};
}