#pragma once

#include <string>
#include <GLFW/glfw3.h>

#include "../Core.h"

namespace KE {

	class KE_API Window {
	public:
		Window(int width, int height, std::string title);
		~Window();

		void onUpdate();

		static Window* create(int width, int height, std::string title);

	private:
		GLFWwindow* m_Window;
	};
}