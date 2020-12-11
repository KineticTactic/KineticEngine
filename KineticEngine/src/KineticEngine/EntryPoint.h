#pragma once

#ifdef KE_PLATFORM_WINDOWS

extern KE::Application* KE::CreateApplication();

int main(int argc, char** argv) {
	KE::Log::Init();
	KE_CORE_WARN("Logging System Initialized!");
	KE_INFO("Hello World!");
	auto app = KE::CreateApplication();
	app->Run();
	delete app;
}

#endif