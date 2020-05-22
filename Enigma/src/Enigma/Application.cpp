#include "engmpch.h"
#include "Application.h"

#include "Enigma/Events/ApplicationEvent.h"
#include "Enigma/Log.h"

#include <GLFW/glfw3.h>

namespace Enigma {

	Application::Application() {
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application() {

	}

	void Application::Run() {
		while (m_Running) {
			glClearColor(0.7f, 0.9f, 0.9f,1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}

}
