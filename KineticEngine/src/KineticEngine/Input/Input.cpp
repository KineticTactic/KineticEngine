#include "kepch.h"
#include "Input.h"

#include "KineticEngine/Core/Application.h"

namespace KE {
	bool  Input::IsKeyPressed(int keycode) {
		GLFWwindow* window = Application::Get().GetWindow().GetNativeWindow();
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(int button) {
		GLFWwindow* window = Application::Get().GetWindow().GetNativeWindow();
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> Input::GetMousePosition() {
		GLFWwindow* window = Application::Get().GetWindow().GetNativeWindow();
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { (float)xpos, (float)ypos };
	}

	float Input::GetMouseX() {
		auto [x, y] = GetMousePosition();

		return x;
	}

	float Input::GetMouseY() {
		auto [x, y] = GetMousePosition();

		return y;
	}
}