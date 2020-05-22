#pragma once
#include "Core.h"
#include "Enigma/Events/ApplicationEvent.h"
#include "Window.h"

namespace Enigma {

	class ENIGMA_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	//to be defined by the Client Application
	Application* CreateApplication();

}
