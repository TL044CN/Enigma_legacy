#include "engmpch.h"
#include "Texture.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Enigma {

	Ref<Texture2D> Texture2D::Create(const std::string& path) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:	ENGM_CORE_ASSERT(false, "RendererAPI::None is not a valid Renderer API"); return nullptr;
		case RendererAPI::API::OpenGL:	return std::make_shared<OpenGLTexture2D>(path);
		}
		ENGM_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}

}