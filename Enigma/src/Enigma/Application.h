#pragma once
#include "Core.h"
#include "Window.h"
#include "Enigma/Layerstack.h"
#include "Enigma/Events/ApplicationEvent.h"

namespace Enigma {

	class ENIGMA_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;
	};

	//to be defined by the Client Application
	Application* CreateApplication();

}
