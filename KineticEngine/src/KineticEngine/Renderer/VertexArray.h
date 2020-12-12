#pragma once

#include "KineticEngine/Renderer/Buffer.h"

namespace KE {

	class VertexArray {
	public:
		VertexArray();
		~VertexArray();

		void Bind() const;
		void Unbind() const;

		void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
		void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);

		inline const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }

		static VertexArray* Create();

	private:
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		uint32_t m_RendererID;
	};

}