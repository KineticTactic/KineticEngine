#include "kepch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace KE {

	struct Renderer2DStorage {
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;
	};

	static Renderer2DStorage* s_Data;

	void Renderer2D::Init() {
		KE_PROFILE_FUNCTION();

		s_Data = new Renderer2DStorage();

		s_Data->QuadVertexArray = VertexArray::Create();

		float sqVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f,	0.0f, 1.0f
		};

		Ref< VertexBuffer> sqVertexBuffer;
		sqVertexBuffer = VertexBuffer::Create(sqVertices, sizeof(sqVertices));
		BufferLayout layout = {
			   {  ShaderDataType::Float3, "a_Position" },
			   {  ShaderDataType::Float2, "a_TexCoord" }
		};
		sqVertexBuffer->SetLayout(layout);
		s_Data->QuadVertexArray->AddVertexBuffer(sqVertexBuffer);

		uint32_t sqIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref< IndexBuffer> sqIndexBuffer;
		sqIndexBuffer = IndexBuffer::Create(sqIndices, sizeof(sqIndices) / sizeof(uint32_t));
		s_Data->QuadVertexArray->SetIndexBuffer(sqIndexBuffer);

		s_Data->WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		s_Data->TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown() {
		KE_PROFILE_FUNCTION();

		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera) {
		KE_PROFILE_FUNCTION();

		s_Data->TextureShader->Bind();
		s_Data->TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene() {
		KE_PROFILE_FUNCTION();
	}


	// ----------------- FLAT COLORED QUAD ----------------------------------------------------------------------------------------------
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
		DrawQuad({ position.x, position.y, 0.f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
		KE_PROFILE_FUNCTION();
		s_Data->WhiteTexture->Bind();
		s_Data->TextureShader->SetFloat4("u_Color", color);
		s_Data->TextureShader->SetFloat("u_TilingFactor", 1.f);
		glm::mat4 transform = glm::translate(glm::mat4(1.f), position) * glm::scale(glm::mat4(1.f), { size.x, size.y, 1.f });
		s_Data->TextureShader->SetMat4("u_Transform", transform);
		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}


	// ----------------- TEXTURED QUAD ----------------------------------
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor) {
		DrawQuad({ position.x, position.y, 0.f }, size, texture, tilingFactor, tintColor);
	}


	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor) {
		KE_PROFILE_FUNCTION();
		texture->Bind();
		s_Data->TextureShader->SetFloat4("u_Color", tintColor);
		s_Data->TextureShader->SetFloat("u_TilingFactor", tilingFactor);
		glm::mat4 transform = glm::translate(glm::mat4(1.f), position) * glm::scale(glm::mat4(1.f), { size.x, size.y, 1.f });
		s_Data->TextureShader->SetMat4("u_Transform", transform);
		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}




	// ----------------- FLAT COLORED ROTATED QUAD ----------------------------------
	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color) {
		DrawRotatedQuad({ position.x, position.y, 0.f }, size, rotation, color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color) {
		KE_PROFILE_FUNCTION();
		s_Data->WhiteTexture->Bind();
		s_Data->TextureShader->SetFloat4("u_Color", color);
		s_Data->TextureShader->SetFloat("u_TilingFactor", 1.f);
		glm::mat4 transform = glm::translate(glm::mat4(1.f), position) * glm::rotate(glm::mat4(1.f), rotation, { 0.f, 0.f, 1.f }) * glm::scale(glm::mat4(1.f), { size.x, size.y, 1.f });
		s_Data->TextureShader->SetMat4("u_Transform", transform);
		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}





	// ----------------- TEXTURED ROTATED QUAD ----------------------------------
	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor) {
		DrawRotatedQuad({ position.x, position.y, 0.f }, size, rotation, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor) {
		KE_PROFILE_FUNCTION();
		texture->Bind();
		s_Data->TextureShader->SetFloat4("u_Color", tintColor);
		s_Data->TextureShader->SetFloat("u_TilingFactor", tilingFactor);
		glm::mat4 transform = glm::translate(glm::mat4(1.f), position) * glm::rotate(glm::mat4(1.f), rotation, { 0.f, 0.f, 1.f }) * glm::scale(glm::mat4(1.f), { size.x, size.y, 1.f });
		s_Data->TextureShader->SetMat4("u_Transform", transform);
		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

}