#include "engmpch.h"
#include "Enigma/Renderer/RenderCommand.h"

namespace Enigma {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}