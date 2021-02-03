#include "engmpch.h"
#include "Enigma/Renderer/Framebuffer.h"

#include "Enigma/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Enigma {

	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecs & spec) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:	ENGM_CORE_ASSERT(false, "RendererAPI::None is not a valid Renderer API"); return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLFramebuffer>(spec);
		}
		ENGM_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}