#include "engmpch.h"
#include "Enigma/Renderer/Buffer.h"
#include "Enigma/Renderer/Renderer.h"

#include "Enigma/Core/Log.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Enigma {

	Ref<VertexBuffer> Enigma::VertexBuffer::Create(float* vertices, uint32_t size) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:	ENGM_CORE_FATAL("{0}", "RendererAPI::None is not a valid renderer API!"); return nullptr;
			case RendererAPI::API::OpenGL:	return CreateRef<OpenGLVertexBuffer>(vertices, size);
		}
		ENGM_CORE_FATAL("{0}", "Unknown Renderer API!");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:	ENGM_CORE_FATAL("{0}", "RendererAPI::None is not a valid renderer API!"); return nullptr;
			case RendererAPI::API::OpenGL:	return CreateRef<OpenGLIndexBuffer>(indices, size);
		}
		ENGM_CORE_FATAL("{0}", "Unknown Renderer API!");
		return nullptr;
	}

}

