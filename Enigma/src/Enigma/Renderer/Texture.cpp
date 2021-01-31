#include "engmpch.h"
#include "Enigma/Renderer/Texture.h"
#include "Enigma/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Enigma {

	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:	ENGM_CORE_ERROR("RendererAPI::None is not a valid Renderer API"); return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLTexture2D>(width, height);
		}
		ENGM_CORE_ERROR("Unknown Renderer API");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string& path) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:	ENGM_CORE_ERROR("RendererAPI::None is not a valid Renderer API"); return nullptr;
		case RendererAPI::API::OpenGL:	return CreateRef<OpenGLTexture2D>(path);
		}
		ENGM_CORE_ERROR("Unknown Renderer API");
		return nullptr;
	}

}