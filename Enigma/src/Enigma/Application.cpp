#include "Application.h"

#include "Enigma/Events/ApplicationEvent.h"
#include "Enigma/Log.h"

namespace Enigma {

	Application::Application() {

	}

	Application::~Application() {

	}

	void Application::Run() {
		WindowResizeEvent e(1280, 720);
		ENGM_CLIENT_TRACE(e);
		while (true);
	}

}
