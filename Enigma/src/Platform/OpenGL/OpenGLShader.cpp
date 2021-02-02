#include "engmpch.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Enigma/Core/Log.h"

#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Enigma {

	static GLenum ShaderTypeFromString(const std::string& type) {
		if(type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment")
			return GL_FRAGMENT_SHADER;
		ENGM_CORE_ERROR("Unknown Shader Type");
	}

	OpenGLShader::OpenGLShader(const std::string& path) {
		ENGM_PROFILE_FUNCTION();

		std::string source = ReadFile(path);
		auto shaderSource = PreProcess(source);
		Compile(shaderSource);

		//get Shader name from File path
		auto lastSlash = path.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = path.rfind('.');
		auto count = lastDot == std::string::npos ? path.size() - lastSlash : lastDot - lastSlash;
		m_Name = path.substr(lastSlash, count);
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource)
	: m_Name(name) {
		ENGM_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSource;
		sources[GL_FRAGMENT_SHADER] = fragmentSource;
		Compile(sources);
	}

	OpenGLShader::~OpenGLShader() {
		ENGM_PROFILE_FUNCTION();

		glDeleteProgram(m_RendererID);
	}

	std::string OpenGLShader::ReadFile(const std::string& path) {
		ENGM_PROFILE_FUNCTION();

		std::string result;
		std::ifstream input(path, std::ios::in | std::ios::binary);
		if (input) {
			//seek eof
			input.seekg(0, std::ios::end);

			//get size of file
			size_t size = input.tellg();
			if (size != -1) {
				//resize result size to actual size of the shader source
				result.resize(size);
				//jump back to the beginning of the file then read it
				input.seekg(0, std::ios::beg);
				input.read(&result[0], size);
				input.close();
			} else {
				ENGM_ERROR("Could not read from file '{0}'", path);
			}
		} else {
			ENGM_CORE_ERROR("Could not open file '{0}'", path);
		}
		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source) {
		ENGM_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::string> sources;
		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos) {
			size_t eol = source.find_first_of("\r\n", pos);
			ENGM_CORE_ASSERT(eol != std::string::npos, "Syntax Error!");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			ENGM_CORE_ASSERT(ShaderTypeFromString(type), "Invalid Shadertype!");
			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			sources[ShaderTypeFromString(type)] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}
		return sources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources) {
		ENGM_PROFILE_FUNCTION();

		GLuint program = glCreateProgram();
		ENGM_CORE_ASSERT(shaderSources.size() <= 2, "Maximum number of shaders is 2 for now.");
		std::array<GLenum, 2> glShaderIDs;
		int glShaderIDIndex = 0;
		for (auto& shaderSource : shaderSources) {
			GLenum type = shaderSource.first;
			const std::string& source = shaderSource.second;
			GLuint shader = glCreateShader(type);
			const GLchar* sourceCString = source.c_str();
			glShaderSource(shader, 1, &sourceCString, 0);
			glCompileShader(shader);
			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE) {
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
				std::vector<GLchar> reason(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &reason[0]);
				glDeleteShader(shader);
				ENGM_CORE_ERROR("Shader Compilation Error:\n{0}", reason.data());
				break;
			}
			glAttachShader(program, shader);
			glShaderIDs[glShaderIDIndex++] = shader;
		}

		m_RendererID = program;

		//link program
		glLinkProgram(program);

		GLint linked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&linked);
		if (linked == GL_FALSE) {
			GLint maxLength = 0;

			//get error message
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);		//get length of the message
			std::vector<GLchar> log(maxLength);									//create buffer for error message
			glGetShaderInfoLog(program, maxLength, &maxLength, &log[0]);	//store log message in buffer
			glDeleteProgram(program);
			for (auto id : glShaderIDs)
				glDeleteShader(id);

			ENGM_CORE_ERROR("{0}", log.data());
			ENGM_CORE_ASSERT(false, "Shaders did not link correctly!");
			return;
		}

		for (auto id : glShaderIDs)
			glDetachShader(program, id);
	}

	void OpenGLShader::Bind() const {
		ENGM_PROFILE_FUNCTION();

		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const {
		ENGM_PROFILE_FUNCTION();

		glUseProgram(0);
	}

	void OpenGLShader::SetInt(const std::string& name, int value) {
		ENGM_PROFILE_FUNCTION();

		UploadUniformInt(name, value);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value) {
		ENGM_PROFILE_FUNCTION();

		UploadUniformFloat3(name, value);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value) {
		ENGM_PROFILE_FUNCTION();

		UploadUniformFloat4(name, value);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value) {
		ENGM_PROFILE_FUNCTION();

		UploadUniformMat4(name, value);
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}
