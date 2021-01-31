#include "engmpch.h"
#include "Enigma/Renderer/RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Enigma {

	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	Scope<RendererAPI> RendererAPI::Create() {
		switch (s_API) {
		case RendererAPI::API::None:	ENGM_CORE_FATAL("{0}", "RendererAPI::None is not a valid renderer API!"); return nullptr;
		case RendererAPI::API::OpenGL:	return CreateScope<OpenGLRendererAPI>();
		}
		ENGM_CORE_FATAL("{0}", "Unknown Renderer API!");
		return nullptr;
	}
}