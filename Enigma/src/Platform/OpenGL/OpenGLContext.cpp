#include "engmpch.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include "Enigma/Core/Log.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <gl/GL.h>

namespace Enigma {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) 
	: m_windowHandle(windowHandle) {
		ENGM_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init() {
		ENGM_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ENGM_CORE_ASSERT(status, "Failed to initialize Glad!");

		ENGM_CORE_INFO("OpenGL Info:");
		ENGM_CORE_INFO("	Vendor: {0}",glGetString(GL_VENDOR));
		ENGM_CORE_INFO("	Renderer: {0}",glGetString(GL_RENDERER));
		ENGM_CORE_INFO("	Version: {0}",glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers() {
		ENGM_PROFILE_FUNCTION();

		glfwSwapBuffers(m_windowHandle);
	}

}
