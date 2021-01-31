#include "engmpch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Enigma {

	Ref<VertexArray> VertexArray::Create() {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:	ENGM_CORE_ASSERT(false, "RendererAPI::None is not a valid Renderer API"); return nullptr;
		case RendererAPI::API::OpenGL:	return std::make_shared<OpenGLVertexArray>();
		}
		ENGM_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}