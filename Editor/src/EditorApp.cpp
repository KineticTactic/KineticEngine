#include <KineticEngine.h>
#include <KineticEngine/Core/EntryPoint.h>

#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "EditorLayer.h"

namespace KE {

	class Editor : public KE::Application {
	public:
		Editor()
			:Application("Kinetic Engine") {
			PushLayer(new EditorLayer());
		}

		~Editor() {

		}
	};

	Application* CreateApplication() {
		return new Editor();
	}
}