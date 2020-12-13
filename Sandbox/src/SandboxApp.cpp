#include <KineticEngine.h>
#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public KE::Layer {
public:
	ExampleLayer()
		: Layer("Example"),
		m_Camera(-1.6f, 1.6f, -0.9f, 0.9f),
		m_CameraPosition(0.0f),
		triPosition(0.f) {
		m_TriVertexArray.reset(KE::VertexArray::Create());


		float triangleVertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<KE::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(KE::VertexBuffer::Create(triangleVertices, sizeof(triangleVertices)));
		KE::BufferLayout layout = {
				{ KE::ShaderDataType::Float3, "a_Position" },
				{ KE::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_TriVertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<KE::IndexBuffer> indexBuffer;
		indexBuffer.reset(KE::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_TriVertexArray->SetIndexBuffer(indexBuffer);

		// ---
		m_SqVertexArray.reset(KE::VertexArray::Create());

		float sqVertices[6 * 7] = {
			 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 1.f, 1.f,
			-0.5f,  0.5f, 0.0f, 0.0f, 0.5f, 1.f, 1.f,
			-0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 1.f, 1.f,
			 0.5f,  0.5f, 0.0f, 0.0f, 0.5f, 1.f, 1.f
		};

		std::shared_ptr<KE::VertexBuffer> sqVertexBuffer;
		sqVertexBuffer.reset(KE::VertexBuffer::Create(sqVertices, sizeof(sqVertices)));
		KE::BufferLayout sqLayout = {
				{ KE::ShaderDataType::Float3, "a_Position" },
				{ KE::ShaderDataType::Float4, "a_Color" }
		};
		sqVertexBuffer->SetLayout(sqLayout);
		m_SqVertexArray->AddVertexBuffer(sqVertexBuffer);

		uint32_t sqIndices[6] = { 0, 1, 2, 1, 0, 3 };
		std::shared_ptr<KE::IndexBuffer> sqIndexBuffer;
		sqIndexBuffer.reset(KE::IndexBuffer::Create(sqIndices, sizeof(sqIndices) / sizeof(uint32_t)));
		m_SqVertexArray->SetIndexBuffer(sqIndexBuffer);



		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(new KE::Shader(vertexSrc, fragmentSrc));
	}

	virtual void OnUpdate(KE::Timestep ts) override {
		KE_INFO(ts.GetSeconds());

		if (KE::Input::IsKeyPressed(KE_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		if (KE::Input::IsKeyPressed(KE_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (KE::Input::IsKeyPressed(KE_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		if (KE::Input::IsKeyPressed(KE_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;

		if (KE::Input::IsKeyPressed(KE_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		if (KE::Input::IsKeyPressed(KE_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		KE::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		KE::RenderCommand::Clear();

		KE::Renderer::BeginScene(m_Camera);

		static glm::mat4 scale = glm::scale(glm::mat4(1.f), glm::vec3(0.05f));
		for (int y = 0; y < 20; y++) {
			for (int x = 0; x < 20; x++) {
				glm::vec3 pos(x * 0.06f, y * 0.06f, 0.f);
				glm::mat4 transform = glm::translate(glm::mat4(1.f), pos) * scale;
				KE::Renderer::Submit(m_Shader, m_SqVertexArray, transform);
			}
		}
		//KE::Renderer::Submit(m_Shader, m_SqVertexArray);
		scale = glm::scale(glm::mat4(1.f), glm::vec3(0.2f));
		KE::Renderer::Submit(m_Shader, m_TriVertexArray, scale);
		KE::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override {

	}

	virtual void OnEvent(KE::Event& event) override {

	}

private:
	std::shared_ptr<KE::VertexArray> m_TriVertexArray;
	std::shared_ptr<KE::VertexArray> m_SqVertexArray;
	std::shared_ptr<KE::Shader> m_Shader;

	KE::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraRotation = 0.f;
	float m_CameraMoveSpeed = 2.f;
	float m_CameraRotationSpeed = 50.0f;

	glm::vec3 triPosition;
};



// -------------------------------------------

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