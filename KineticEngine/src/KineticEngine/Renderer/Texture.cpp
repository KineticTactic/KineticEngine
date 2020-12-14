#include "kepch.h"
#include "Texture.h"

#include <glad/glad.h>
#include <stb_image.h>

namespace KE {

	Texture2D::Texture2D(const std::string& path)
		:m_Path(path) {
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
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

		KE_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	Texture2D::~Texture2D() {
		glDeleteTextures(1, &m_RendererID);
	}

	uint32_t Texture2D::GetWidth() const {
		return m_Width;
	}

	uint32_t Texture2D::GetHeight() const {
		return m_Height;
	}

	void Texture2D::Bind(uint32_t slot) const {
		glBindTextureUnit(slot, m_RendererID);
	}

	Ref<KE::Texture2D> Texture2D::Create(const std::string& path) {
		return std::make_shared<Texture2D>(path);
	}

}
