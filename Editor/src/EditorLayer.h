#pragma once

#include <KineticEngine.h>

#include "Panels/SceneHierarchyPanel.h"

#include "KineticEngine/Renderer/EditorCamera.h"

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
		bool OnKeyPressed(KeyPressedEvent& e);

		void NewScene();
		void OpenScene();
		void SaveSceneAs();

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

		EditorCamera m_EditorCamera;

		bool m_ViewportFocused = false, m_ViewportHovered = false;
		glm::vec2 m_ViewportSize = { 0.f, 0.f };

		int m_GizmoType = -1;

		// Panels
		SceneHierarchyPanel m_SceneHierarchyPanel;
	};

}