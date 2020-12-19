#pragma once

#include "KineticEngine/Core/Core.h"
#include "KineticEngine/Core/Log.h"
#include "KineticEngine/Scene/Scene.h"
#include "KineticEngine/Scene/Entity.h"

namespace KE {

	class SceneHierarchyPanel {
	public:
		SceneHierarchyPanel() {}
		SceneHierarchyPanel(const Ref<Scene>& context);

		void SetContext(const Ref<Scene>& context);

		void OnImGuiRender();

	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);

	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};

}