#include "engmpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Enigma {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}