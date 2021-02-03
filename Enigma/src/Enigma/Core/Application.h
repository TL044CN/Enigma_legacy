#pragma once
#include "Enigma/Core.h"
#include "Enigma/Core/Window.h"
#include "Enigma/Core/Layerstack.h"
#include "Enigma/Events/Event.h"
#include "Enigma/Events/ApplicationEvent.h"
#include "Enigma/Core/Timestep.h"
#include "Enigma/ImGui/ImGuiLayer.h"

namespace Enigma {

	class Application {
	public:
		Application(const std::string& name = "Enigma Engine");
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		Window& GetWindow() { return *m_Window; }

		void Close();

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

		static Application* s_Instance;
	};

	//to be defined by the Client Application
	Application* CreateApplication();

}
