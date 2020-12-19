#include "EditorLayer.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp> 
#include <glm/gtc/random.hpp>

namespace KE {

	EditorLayer::EditorLayer()
		:Layer("EditorLayer"),
		m_CameraController(1280.0f / 720.0f, true) {

	}

	void EditorLayer::OnAttach() {
		KE_PROFILE_FUNCTION();

		m_Texture = Texture2D::Create("assets/textures/Container.png");
		m_Spritesheet = Texture2D::Create("assets/textures/Spritesheet.png");

		m_TextureVortex = SubTexture2D::CreateFromCoords(m_Spritesheet, { 11, 6 }, { 128, 128 });
		m_TextureDoor = SubTexture2D::CreateFromCoords(m_Spritesheet, { 6, 0 }, { 128, 128 }, { 1, 2 });

		FramebufferSpecification fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		m_Framebuffer = Framebuffer::Create(fbSpec);

		m_ActiveScene = CreateRef<Scene>();

		m_SquareEntity = m_ActiveScene->CreateEntity("Square");
		m_SquareEntity.AddComponent<SpriteRendererComponent>(glm::vec4{ 0.f, 1.f, 0.2f, 1.f });

		m_CameraEntity = m_ActiveScene->CreateEntity("Camera");
		m_CameraEntity.AddComponent<CameraComponent>();


		class CameraController : public ScriptableEntity {
		public:
			void OnCreate() {
				std::cout << "OnCreate" << std::endl;
			}

			void OnDestroy() {

			}

			void OnUpdate(Timestep ts) {
				auto& transform = GetComponent<TransformComponent>().Transform;
				float speed = 5.0f;

				if (Input::IsKeyPressed(KE_KEY_A))
					transform[3][0] -= speed * ts;
				if (Input::IsKeyPressed(KE_KEY_D))
					transform[3][0] += speed * ts;
				if (Input::IsKeyPressed(KE_KEY_W))
					transform[3][1] += speed * ts;
				if (Input::IsKeyPressed(KE_KEY_S))
					transform[3][1] -= speed * ts;
			}
		};

		m_CameraEntity.AddComponent<NativeScriptComponent>().Bind<CameraController>();
	}

	void EditorLayer::OnDetach() {
		KE_PROFILE_FUNCTION();
	}

	void EditorLayer::OnUpdate(Timestep ts) {
		KE_PROFILE_FUNCTION();

		m_Ts = ts;

		// Resize
		FramebufferSpecification spec = m_Framebuffer->GetSpecification();
		if (m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && (spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y)) {
			m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
			m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);

			m_ActiveScene->OnViewportResize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
		}

		// Update
		if (m_ViewportFocused) {
			m_CameraController.OnUpdate(ts);
		}


		// Render
		Renderer2D::ResetStats();
		m_Framebuffer->Bind();
		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.f });
		RenderCommand::Clear();

		m_ActiveScene->OnUpdate(ts);

		m_Framebuffer->Unbind();
	}

	void EditorLayer::OnImGuiRender() {
		KE_PROFILE_FUNCTION();

		static bool dockspaceOpen = true;
		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->GetWorkPos());
			ImGui::SetNextWindowSize(viewport->GetWorkSize());
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Quit")) Application::Get().Close();
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}



		ImGui::Begin("Settings");

		float fps = 1.f / m_Ts.GetSeconds();
		ImGui::Text(std::to_string(fps).c_str());

		auto stats = Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());


		ImGui::Separator();
		ImGui::Text("%s", m_SquareEntity.GetComponent<TagComponent>().Tag.c_str());
		auto& squareColor = m_SquareEntity.GetComponent<SpriteRendererComponent>().Color;
		ImGui::ColorEdit4("Square Color", glm::value_ptr(squareColor));
		ImGui::Separator();

		ImGui::Separator();
		ImGui::DragFloat3("Camera Transform", glm::value_ptr(m_CameraEntity.GetComponent<TransformComponent>().Transform[3]), 0.1f);
		auto& camera = m_CameraEntity.GetComponent<CameraComponent>().Camera;
		float orthoSize = camera.GetOrthoGraphicSize();
		if (ImGui::DragFloat("Camera Zoom", &orthoSize)) {
			camera.SetOrthoGraphicSize(orthoSize);
		}
		ImGui::Separator();


		ImGui::End();



		// Viewport Panel
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Viewport");

		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);


		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		if (m_ViewportSize != *((glm::vec2*)&viewportPanelSize)) {
			m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
		}

		uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)textureID, ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		ImGui::End();
		ImGui::PopStyleVar();


		ImGui::End();

	}

	void EditorLayer::OnEvent(Event& e) {
		m_CameraController.OnEvent(e);
	}

}