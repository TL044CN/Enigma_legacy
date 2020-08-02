#include "engmpch.h"
#include "Shader.h"

#include "Enigma/Log.h"

#include <glad/glad.h>

namespace Enigma {

	Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource) {
		//Create empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// send vertex shader source to GL
		const GLchar* source = vertexSource.c_str();
		glShaderSource(vertexShader, 1, &source, 0);
		glCompileShader(vertexShader);					//compile shader

		GLint compiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compiled);
		if (compiled == GL_FALSE) {
			GLint maxLength = 0;

			//get error message
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);		//get length of the message
			std::vector<GLchar> log(maxLength);									//create buffer for error message
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &log[0]);	//store log message in buffer

			glDeleteShader(vertexShader);

			ENGM_CORE_ERROR("{0}", log.data());
			ENGM_CORE_ASSERT(false, "Vertex shader did not compile!");
			return;
		}

		//create empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		//send fragment shader source to GL
		source = fragmentSource.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);
		glCompileShader(fragmentShader);				//compile shader

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compiled);
		if (compiled == GL_FALSE) {
			GLint maxLength = 0;

			//get error message
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);		//get length of the message
			std::vector<GLchar> log(maxLength);									//create buffer for error message
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &log[0]);	//store log message in buffer

			//delete both shaders upon error
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			ENGM_CORE_ERROR("{0}", log.data());
			ENGM_CORE_ASSERT(false, "Fragment shader did not compile!");
			return;
		}

		/*	link compiled shaders into program	*/

		//create new program
		m_rendererID = glCreateProgram();
		GLuint program = m_rendererID;

		//attach shaders to program
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

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

			//delete program and shaders
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
			glDeleteProgram(program);

			ENGM_CORE_ERROR("{0}", log.data());
			ENGM_CORE_ASSERT(false, "Shaders did not link correctly!");
			return;
		}

		//detach shaders after successfull link
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
	}

	Shader::~Shader() {
		glDeleteProgram(m_rendererID);
	}

	void Shader::Bind() const {
		glUseProgram(m_rendererID);
	}

	void Shader::Unbind() const {
		glUseProgram(0);
	}
}
