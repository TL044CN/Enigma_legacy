#include "engmpch.h"
#include "Enigma/Renderer/GraphicsContext.h"

#include "Enigma/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Enigma {

	Scope<GraphicsContext> GraphicsContext::Create(void* window) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:	ENGM_CORE_ASSERT(false, "RendererAPI::None is not a valid Renderer API"); return nullptr;
		case RendererAPI::API::OpenGL:	return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}
		ENGM_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}
