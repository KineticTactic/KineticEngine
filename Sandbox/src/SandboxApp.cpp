#include <KineticEngine.h>
#include <imgui/imgui.h>

class ExampleLayer : public KE::Layer {
public:
	ExampleLayer()
		: Layer("Example") {
	}

	virtual void OnUpdate() override {

	}

	virtual void OnImGuiRender() override {
		ImGui::Begin("From Sandbox");
		ImGui::Text("Hello Sandbox!");
		ImGui::End();
	}

	virtual void OnEvent(KE::Event& event) override {
		//KE_TRACE("{0}", event);
	}
};

class Sandbox : public KE::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {

	}
};

KE::Application* KE::CreateApplication() {
	return new Sandbox();
}