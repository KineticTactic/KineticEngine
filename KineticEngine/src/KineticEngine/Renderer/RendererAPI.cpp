#include "kepch.h"
#include "RendererAPI.h"

#include <glad/glad.h>

namespace KE {

	void RendererAPI::Init() {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void RendererAPI::SetClearColor(const glm::vec4& color) {
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void RendererAPI::Clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void RendererAPI::DrawIndexed(const Ref<VertexArray>& vertexAray) {
		glDrawElements(GL_TRIANGLES, vertexAray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

}