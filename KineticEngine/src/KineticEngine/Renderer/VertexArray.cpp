#include "kepch.h"
#include "VertexArray.h"

#include <glad/glad.h>

namespace KE {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case KE::ShaderDataType::Float:    return GL_FLOAT;
		case KE::ShaderDataType::Float2:   return GL_FLOAT;
		case KE::ShaderDataType::Float3:   return GL_FLOAT;
		case KE::ShaderDataType::Float4:   return GL_FLOAT;
		case KE::ShaderDataType::Mat3:     return GL_FLOAT;
		case KE::ShaderDataType::Mat4:     return GL_FLOAT;
		case KE::ShaderDataType::Int:      return GL_INT;
		case KE::ShaderDataType::Int2:     return GL_INT;
		case KE::ShaderDataType::Int3:     return GL_INT;
		case KE::ShaderDataType::Int4:     return GL_INT;
		case KE::ShaderDataType::Bool:     return GL_BOOL;
		}

		KE_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	VertexArray::VertexArray() {
		glCreateVertexArrays(1, &m_RendererID);
	}

	VertexArray::~VertexArray() {

	}

	void VertexArray::Bind() const {
		glBindVertexArray(m_RendererID);
	}

	void VertexArray::Unbind() const {
		glBindVertexArray(0);
	}

	void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) {
		KE_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			index++;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}

	void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) {
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

	VertexArray* VertexArray::Create() {
		return new VertexArray();
	}
}