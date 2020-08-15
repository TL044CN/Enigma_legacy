#pragma once

#include <string>
#include <glm/glm.hpp>
namespace Enigma {

	class Shader {
	public:
		~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Shader* Create(const std::string& vertexSource, const std::string& fragmentSource);
	private:
		uint32_t m_rendererID;
	};

}
