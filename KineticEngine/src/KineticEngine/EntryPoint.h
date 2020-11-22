#pragma once

#ifdef KE_PLATFORM_WINDOWS

extern KE::Application* KE::createApplication();

int main(int argc, char** argv) {
	KE::Log::init();
	KE_CORE_WARN("Logging System Initialized!");
	KE_INFO("Hello World!");
	auto app = KE::createApplication();
	app->run();
	delete app;
}

#endif