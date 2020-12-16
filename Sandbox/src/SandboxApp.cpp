#include <KineticEngine.h>
#include <KineticEngine/Core/EntryPoint.h>

#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"
#include "Pong/Pong.h"

class ExampleLayer : public KE::Layer {
public:
	ExampleLayer()
		: Layer("Example"),
		m_CameraController(1280.0f / 720.0f, true),
		m_SquareColor(0.f, 0.5f, 1.f, 1.f) {
		m_TriVertexArray = KE::VertexArray::Create();


		float triangleVertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		KE::Ref<KE::VertexBuffer> vertexBuffer;
		vertexBuffer = KE::VertexBuffer::Create(triangleVertices, sizeof(triangleVertices));
		KE::BufferLayout layout = {
				{ KE::ShaderDataType::Float3, "a_Position" },
				{ KE::ShaderDataType::Float2, "a_TexCoord" },
		};
		vertexBuffer->SetLayout(layout);
		m_TriVertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		KE::Ref<KE::IndexBuffer> indexBuffer;
		indexBuffer = KE::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_TriVertexArray->SetIndexBuffer(indexBuffer);

		// ---
		m_SqVertexArray = KE::VertexArray::Create();

		float sqVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f,	0.0f, 1.0f
		};

		KE::Ref<KE::VertexBuffer> sqVertexBuffer;
		sqVertexBuffer = KE::VertexBuffer::Create(sqVertices, sizeof(sqVertices));
		sqVertexBuffer->SetLayout(layout);
		m_SqVertexArray->AddVertexBuffer(sqVertexBuffer);

		uint32_t sqIndices[6] = { 0, 1, 2, 2, 3, 0 };
		KE::Ref<KE::IndexBuffer> sqIndexBuffer;
		sqIndexBuffer = KE::IndexBuffer::Create(sqIndices, sizeof(sqIndices) / sizeof(uint32_t));
		m_SqVertexArray->SetIndexBuffer(sqIndexBuffer);


		auto flatColorShader = m_ShaderLibrary.Load("assets/shaders/FlatColor.glsl");
		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = KE::Texture2D::Create("assets/textures/Container.png");
		m_PusheenTexture = KE::Texture2D::Create("assets/textures/pikachu.png");
		textureShader->Bind();
		textureShader->SetInt("u_Texture", 0);
	}

	virtual void OnUpdate(KE::Timestep ts) override {
		m_CameraController.OnUpdate(ts);

		KE::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		KE::RenderCommand::Clear();

		KE::Renderer::BeginScene(m_CameraController.GetCamera());

		static glm::mat4 scale = glm::scale(glm::mat4(1.f), glm::vec3(0.1f));

		auto flatColorShader = m_ShaderLibrary.Get("FlatColor");
		flatColorShader->Bind();
		flatColorShader->SetFloat4("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++) {
			for (int x = 0; x < 20; x++) {
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.f);
				glm::mat4 transform = glm::translate(glm::mat4(1.f), pos) * scale;
				KE::Renderer::Submit(flatColorShader, m_SqVertexArray, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		KE::Renderer::Submit(textureShader, m_SqVertexArray, glm::scale(glm::mat4(1.f), glm::vec3(1.5f)));
		m_PusheenTexture->Bind();
		KE::Renderer::Submit(textureShader, m_SqVertexArray, glm::scale(glm::mat4(1.f), glm::vec3(1.5f)));
		//KE::Renderer::Submit(m_Shader, m_SqVertexArray);
		//m_Shader->UploadUniformFloat3("u_Color", { 0.8f, 0.2f, 0.3f });
		//KE::Renderer::Submit(m_Shader, m_TriVertexArray, glm::scale(glm::mat4(1.f), glm::vec3(0.2f)));

		KE::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override {
		ImGui::Begin("Settings");
		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	virtual void OnEvent(KE::Event& e) override {
		m_CameraController.OnEvent(e);
	}

private:
	KE::ShaderLibrary m_ShaderLibrary;
	KE::Ref<KE::VertexArray> m_TriVertexArray;
	KE::Ref<KE::VertexArray> m_SqVertexArray;

	KE::Ref<KE::Texture2D> m_Texture, m_PusheenTexture;

	KE::OrthographicCameraController m_CameraController;

	glm::vec4 m_SquareColor;
};



// -------------------------------------------

class Sandbox : public KE::Application {
public:
	Sandbox() {
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
		//PushLayer(new Pong());
	}

	~Sandbox() {

	}
};

KE::Application* KE::CreateApplication() {
	return new Sandbox();
}