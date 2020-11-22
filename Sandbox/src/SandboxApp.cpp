#include <KineticEngine.h>

class Sandbox : public KE::Application {
public:
	Sandbox() {

	}

	~Sandbox() {

	}
};

KE::Application* KE::createApplication() {
	return new Sandbox();
}