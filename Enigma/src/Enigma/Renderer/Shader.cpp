#include "engmpch.h"
#include "Shader.h"

#include "Enigma/Log.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Enigma {

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:	ENGM_CORE_ASSERT(false, "RendererAPI:None is not supported"); return nullptr;
		case RendererAPI::API::OpenGL:	return new OpenGLShader(vertexSrc, fragmentSrc);
		}
		ENGM_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}

}