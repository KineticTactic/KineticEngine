#pragma once

#include "KineticEngine/Core/Core.h"

namespace KE {

	struct FramebufferSpecification {
		uint32_t Width, Height;
		uint32_t Samples = 1;

		bool SwapChainTarget = false;
	};

	class Framebuffer {
	public:
		Framebuffer(const FramebufferSpecification& spec);
		~Framebuffer();

		const FramebufferSpecification& GetSpecification() const { return m_Specification; }
		uint32_t GetColorAttachmentRendererID() const { return m_ColorAttachment; }

		void Invalidate();
		void Resize(uint32_t width, uint32_t height);

		void Bind();
		void Unbind();

		static Ref<Framebuffer> Create(const FramebufferSpecification& spec);

	private:
		uint32_t m_RendererID = 0;
		uint32_t m_ColorAttachment = 0, m_DepthAttachment = 0;
		FramebufferSpecification m_Specification;
	};
}

