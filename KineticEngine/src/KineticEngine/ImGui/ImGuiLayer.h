#pragma once

#include "KineticEngine/Layer.h"
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
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};
}