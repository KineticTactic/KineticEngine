#pragma once

#ifdef KE_PLATFORM_WINDOWS

extern KE::Application* KE::CreateApplication();

int main(int argc, char** argv) {
	KE::Log::Init();

	KE_PROFILE_BEGIN_SESSION("Startup", "KEProfile-Startup.json");
	auto app = KE::CreateApplication();
	KE_PROFILE_END_SESSION();

	KE_PROFILE_BEGIN_SESSION("Runtime", "KEProfile-Runtime.json");
	app->Run();
	KE_PROFILE_END_SESSION();

	KE_PROFILE_BEGIN_SESSION("Shutdown", "KEProfile-Shutdown.json");
	delete app;
	KE_PROFILE_END_SESSION();
}

#endif