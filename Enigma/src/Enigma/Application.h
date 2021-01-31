#pragma once
#include "Core.h"
#include "Window.h"
#include "Enigma/Layerstack.h"
#include "Enigma/Events/Event.h"
#include "Enigma/Events/ApplicationEvent.h"
#include "Enigma/Core/Timestep.h"
#include "Enigma/ImGui/ImGuiLayer.h"

namespace Enigma {

	class Application {
	public:
		Application();
		virtual ~Application() = default;

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

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
