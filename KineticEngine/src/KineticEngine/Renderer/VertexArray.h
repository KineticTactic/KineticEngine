#pragma once

#include "KineticEngine/Renderer/Buffer.h"

namespace KE {

	class VertexArray {
	public:
		VertexArray();
		~VertexArray();

		void Bind() const;
		void Unbind() const;

		void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer);
		void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer);

		inline const Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }

		static VertexArray* Create();

	private:
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
		uint32_t m_RendererID;
	};

}