#pragma once
#include "Core.h"
#include "Window.h"
#include "Enigma/Layerstack.h"
#include "Enigma/Events/ApplicationEvent.h"

#include "Enigma/ImGui/ImGuiLayer.h"

#include "Enigma/Renderer/Shader.h"
#include "Enigma/Renderer/Buffer.h"

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
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_vertexArray;
		std::unique_ptr<Shader> m_shader;
		std::unique_ptr<VertexBuffer> m_vertexBuffer;
		std::unique_ptr<IndexBuffer> m_indexBuffer;
	private:
		static Application* s_Instance;
	};

	//to be defined by the Client Application
	Application* CreateApplication();

}
