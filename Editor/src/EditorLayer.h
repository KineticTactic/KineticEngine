#pragma once

#include <KineticEngine.h>

#include "Panels/SceneHierarchyPanel.h"

namespace KE {

	class EditorLayer : public Layer {
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& e) override;

	private:
		OrthographicCameraController m_CameraController;
		Ref<Framebuffer> m_Framebuffer;

		Ref<Scene> m_ActiveScene;
		Entity m_SquareEntity;
		Entity m_CameraEntity;

		glm::vec4 m_SquareColor = { 0.f, 0.5f, 1.f, 1.f };

		Ref<Texture2D> m_Texture;
		Ref<Texture2D> m_Spritesheet;
		Ref<SubTexture2D> m_TextureVortex, m_TextureDoor;

		Timestep m_Ts;

		bool m_ViewportFocused = false, m_ViewportHovered = false;
		glm::vec2 m_ViewportSize = { 0.f, 0.f };

		// Panels
		SceneHierarchyPanel m_SceneHierarchyPanel;
	};

}