#pragma once

#include "Enigma/Renderer/Framebuffer.h"

namespace Enigma {

	class OpenGLFramebuffer : public Framebuffer {
	public:
		OpenGLFramebuffer(const FramebufferSpecs& spec);
		virtual ~OpenGLFramebuffer();

		void Invalidate();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void Resize(uint32_t width, uint32_t height) override;

		virtual uint32_t GetColorAttachmentRendererID()const override { return m_ColorAttachment; }

		virtual const FramebufferSpecs& GetSpecs() const override { return m_Spec; }

	private:
		uint32_t m_RendererID = 0;
		uint32_t m_ColorAttachment = 0;
		uint32_t m_DepthAttachment = 0;
		
		FramebufferSpecs m_Spec;
	};

}