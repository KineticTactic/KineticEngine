#pragma once

#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Shader.h"

namespace KE {
	class Renderer {
	public:
		static void Init();

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.f));

		static void OnWindowResize(uint32_t width, uint32_t height);
	private:
		struct SceneData {
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}