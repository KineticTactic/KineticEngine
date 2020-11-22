#pragma once

#ifdef KE_PLATFORM_WINDOWS

extern KE::Application* KE::createApplication();

int main(int argc, char** argv) {
	auto app = KE::createApplication();
	app->run();
	delete app;
}

#endif