#pragma once

#include "Core.h"

namespace KE {

	class KE_API Application {
	public:
		Application();
		virtual ~Application();

		void run();
	};

	// To be defined in client
	Application* createApplication();

}