#pragma once

#include <string>
#include <functional>

#include "KineticEngine/Renderer/GraphicsContext.h"
#include "KineticEngine/Core.h"
#include "KineticEngine/Events/Event.h"

namespace KE {

	class KE_API Window {
	public:
		Window(int width, int height, std::string title);
		~Window();

		using EventCallbackFn = std::function<void(Event&)>;

		void OnUpdate();

		static Window* Create(int width, int height, std::string title);

		void SetEventCallback(const EventCallbackFn& callback);

		inline unsigned int GetWidth() { return this->m_Data.Width; }
		inline unsigned int GetHeight() { return this->m_Data.Height; }
		inline GLFWwindow* GetNativeWindow() { return this->m_Window; }

	private:
		GLFWwindow* m_Window;

		GraphicsContext* m_Context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}