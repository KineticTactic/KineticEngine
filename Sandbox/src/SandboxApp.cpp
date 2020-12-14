#include <KineticEngine.h>
#include <imgui/imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public KE::Layer {
public:
	ExampleLayer()
		: Layer("Example"),
		m_Camera(-1.6f, 1.6f, -0.9f, 0.9f),
		m_CameraPosition(0.0f),
		m_SquareColor(0.f, 0.f, 0.f) {
		m_TriVertexArray.reset(KE::VertexArray::Create());


		float triangleVertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		KE::Ref<KE::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(KE::VertexBuffer::Create(triangleVertices, sizeof(triangleVertices)));
		KE::BufferLayout layout = {
				{ KE::ShaderDataType::Float3, "a_Position" },
				{ KE::ShaderDataType::Float2, "a_TexCoord" },
		};
		vertexBuffer->SetLayout(layout);
		m_TriVertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		KE::Ref<KE::IndexBuffer> indexBuffer;
		indexBuffer.reset(KE::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_TriVertexArray->SetIndexBuffer(indexBuffer);

		// ---
		m_SqVertexArray.reset(KE::VertexArray::Create());

		float sqVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f,	0.0f, 1.0f
		};

		KE::Ref<KE::VertexBuffer> sqVertexBuffer;
		sqVertexBuffer.reset(KE::VertexBuffer::Create(sqVertices, sizeof(sqVertices)));
		sqVertexBuffer->SetLayout(layout);
		m_SqVertexArray->AddVertexBuffer(sqVertexBuffer);

		uint32_t sqIndices[6] = { 0, 1, 2, 2, 3, 0 };
		KE::Ref<KE::IndexBuffer> sqIndexBuffer;
		sqIndexBuffer.reset(KE::IndexBuffer::Create(sqIndices, sizeof(sqIndices) / sizeof(uint32_t)));
		m_SqVertexArray->SetIndexBuffer(sqIndexBuffer);



		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader.reset(KE::Shader::Create(vertexSrc, fragmentSrc));


		std::string textureShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;

			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string textureShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec2 v_TexCoord;

			uniform sampler2D u_Texture;

			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";

		m_TextureShader.reset(KE::Shader::Create(textureShaderVertexSrc, textureShaderFragmentSrc));

		m_Texture = KE::Texture2D::Create("assets/textures/Checkerboard.png");
		m_PusheenTexture = KE::Texture2D::Create("assets/textures/pusheen.png");
		m_TextureShader->Bind();
		m_TextureShader->UploadUniformInt("u_Texture", 0);
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

		m_FlatColorShader->Bind();
		m_FlatColorShader->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++) {
			for (int x = 0; x < 20; x++) {
				glm::vec3 pos(x * 0.06f, y * 0.06f, 0.f);
				glm::mat4 transform = glm::translate(glm::mat4(1.f), pos) * scale;
				KE::Renderer::Submit(m_FlatColorShader, m_SqVertexArray, transform);
			}
		}

		m_Texture->Bind();
		KE::Renderer::Submit(m_TextureShader, m_SqVertexArray, glm::scale(glm::mat4(1.f), glm::vec3(1.5f)));
		m_PusheenTexture->Bind();
		KE::Renderer::Submit(m_TextureShader, m_SqVertexArray, glm::scale(glm::mat4(1.f), glm::vec3(1.5f)));
		//KE::Renderer::Submit(m_Shader, m_SqVertexArray);
		//m_Shader->UploadUniformFloat3("u_Color", { 0.8f, 0.2f, 0.3f });
		//KE::Renderer::Submit(m_Shader, m_TriVertexArray, glm::scale(glm::mat4(1.f), glm::vec3(0.2f)));

		KE::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override {
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	virtual void OnEvent(KE::Event& event) override {

	}

private:
	KE::Ref<KE::VertexArray> m_TriVertexArray;
	KE::Ref<KE::VertexArray> m_SqVertexArray;
	KE::Ref<KE::Shader> m_FlatColorShader, m_TextureShader;

	KE::Ref<KE::Texture2D> m_Texture, m_PusheenTexture;

	KE::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraRotation = 0.f;
	float m_CameraMoveSpeed = 2.f;
	float m_CameraRotationSpeed = 50.0f;

	glm::vec3 m_SquareColor;
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