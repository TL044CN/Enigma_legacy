#include "engmpch.h"
#include "Buffer.h"
#include "Renderer.h"

#include "Enigma/Log.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Enigma {

	VertexBuffer* Enigma::VertexBuffer::Create(float* vertices, uint32_t size) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::None:		ENGM_CORE_FATAL("{0}", "RendererAPI::None is not a valid renderer API!"); return nullptr;
			case RendererAPI::OpenGL:	return new OpenGLVertexBuffer(vertices, size);
		}
		ENGM_CORE_FATAL("{0}", "Unknown Renderer API!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::None:		ENGM_CORE_FATAL("{0}", "RendererAPI::None is not a valid renderer API!"); return nullptr;
			case RendererAPI::OpenGL:	return new OpenGLIndexBuffer(indices, size);
		}
		ENGM_CORE_FATAL("{0}", "Unknown Renderer API!");
		return nullptr;
	}

}

