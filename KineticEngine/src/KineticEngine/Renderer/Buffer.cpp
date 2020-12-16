#include "kepch.h"
#include "Buffer.h"

#include <glad/glad.h>

namespace KE {

	VertexBuffer::VertexBuffer(float* vertices, uint32_t size) {
		KE_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	VertexBuffer::~VertexBuffer() {
		KE_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_RendererID);
	}

	void VertexBuffer::Bind() const {
		KE_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void VertexBuffer::Unbind() const {
		KE_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size) {
		return std::make_shared<VertexBuffer>(vertices, size);
	}

	// -----------------
	IndexBuffer::IndexBuffer(uint32_t* indices, uint32_t count)
		:m_Count(count) {
		KE_PROFILE_FUNCTION();

		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	IndexBuffer::~IndexBuffer() {
		KE_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_RendererID);
	}

	void IndexBuffer::Bind() const {
		KE_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void IndexBuffer::Unbind() const {
		KE_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	uint32_t IndexBuffer::GetCount() const {
		return m_Count;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size) {
		return std::make_shared<IndexBuffer>(indices, size);
	}

}