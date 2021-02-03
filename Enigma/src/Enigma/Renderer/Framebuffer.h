#pragma once

#include "Enigma/Core.h"

namespace Enigma {

	struct FramebufferSpecs {
		uint32_t Width;
		uint32_t Height;

		uint32_t Samples = 1;

		bool SwapChainTarget = false;
	};

	class Framebuffer {
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;

		virtual uint32_t GetColorAttachmentRendererID() const = 0;

		virtual const FramebufferSpecs& GetSpecs() const = 0;

		static Ref<Framebuffer> Create(const FramebufferSpecs & spec);
	};

}