#pragma once

#include <glm/glm.hpp>

#include "VertexArray.h"

namespace KE {
	class RendererAPI {
	public:
		void SetClearColor(const glm::vec4& color);
		void Clear();

		void DrawIndexed(const std::shared_ptr<VertexArray>& vertexARray);
	};
}