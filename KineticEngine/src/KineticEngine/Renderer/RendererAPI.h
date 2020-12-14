#pragma once

#include <glm/glm.hpp>

#include "VertexArray.h"

namespace KE {
	class RendererAPI {
	public:
		void Init();
		void SetClearColor(const glm::vec4& color);
		void Clear();

		void DrawIndexed(const Ref<VertexArray>& vertexARray);
	};
}