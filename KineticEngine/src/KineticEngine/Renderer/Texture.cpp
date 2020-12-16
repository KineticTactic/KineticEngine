#include "kepch.h"
#include "Texture.h"

#include <glad/glad.h>

#include <stb_image.h>

namespace KE {

	Texture2D::Texture2D(const std::string& path)
		:m_Path(path) {
		KE_PROFILE_FUNCTION();

		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);

		stbi_uc* data;
		{
			KE_PROFILE_SCOPE("stbi_load - Texture2D::Texture2D(const std::string&)");
			data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		}

		KE_CORE_ASSERT(data, "Failed to load image!" + path);
		m_Width = width;
		m_Height = height;

		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4) {
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3) {
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		m_InternalFormat = internalFormat;
		m_DataFormat = dataFormat;

		KE_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	Texture2D::Texture2D(uint32_t width, uint32_t height)
		: m_Width(width), m_Height(height) {
		KE_PROFILE_FUNCTION();

		m_InternalFormat = GL_RGBA8, m_DataFormat = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	Texture2D::~Texture2D() {
		KE_PROFILE_FUNCTION();

		glDeleteTextures(1, &m_RendererID);
	}

	uint32_t Texture2D::GetWidth() const {
		return m_Width;
	}

	uint32_t Texture2D::GetHeight() const {
		return m_Height;
	}

	void Texture2D::SetData(void* data, uint32_t size) {
		KE_PROFILE_FUNCTION();

		uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
		KE_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must be the entire texture!");
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}

	void Texture2D::Bind(uint32_t slot) const {
		KE_PROFILE_FUNCTION();

		glBindTextureUnit(slot, m_RendererID);
	}

	Ref<KE::Texture2D> Texture2D::Create(const std::string& path) {
		return CreateRef<Texture2D>(path);
	}

	KE::Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height) {
		return CreateRef<Texture2D>(width, height);
	}

}
