#include <KineticEngine.h>

class ExampleLayer : public KE::Layer {
public:
	ExampleLayer()
		: Layer("Example") {
	}

	void OnUpdate() override {
		//KE_INFO("ExampleLayer::Update");
		if (KE::Input::IsKeyPressed(KE_KEY_A)) {
			KE_TRACE("A KEY PRESSED!!!!");
		}
	}

	void OnEvent(KE::Event& event) override {
		//KE_TRACE("{0}", event);
	}
};

class Sandbox : public KE::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
		PushOverlay(new KE::ImGuiLayer());
	}

	~Sandbox() {

	}
};

KE::Application* KE::CreateApplication() {
	return new Sandbox();
}