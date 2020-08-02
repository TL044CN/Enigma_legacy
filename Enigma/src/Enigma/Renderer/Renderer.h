#pragma once

namespace Enigma {

	enum class RendererAPI {
		None = 0, OpenGL
	};

	class Renderer {
	public:
		inline static RendererAPI GetAPI() { return s_rendererAPI; }
	private:
		static RendererAPI s_rendererAPI;
	};

}