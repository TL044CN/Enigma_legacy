#include "engmpch.h"
#include "Enigma/Core/Application.h"

#include "Enigma/Core/Log.h"
#include "Enigma/Renderer/Renderer.h"
#include "Enigma/Core/Input.h"
#include <GLFW/glfw3.h>

namespace Enigma {


	Application* Application::s_Instance = nullptr;

	Application::Application(const std::string& name) {
		ENGM_PROFILE_FUNCTION();

		ENGM_CORE_ASSERT(!s_Instance, "Application already Exists!");
		s_Instance = this;

		m_Window = Window::Create(WindowProperties(name));
		m_Window->SetEventCallback(ENGM_BIND_EVENT_FUNCTION(Application::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

	}

	Application::~Application() {
		ENGM_PROFILE_FUNCTION();

		Renderer::Shutdown();
	}

	void Application::PushLayer(Layer* layer) {
		ENGM_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

		
	void Application::PushOverlay(Layer* overlay) {
		ENGM_PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::Close() {
		m_Running = false;
	}

	void Application::OnEvent(Event& e) {
		ENGM_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowCloseEvent>(ENGM_BIND_EVENT_FUNCTION(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(ENGM_BIND_EVENT_FUNCTION(Application::OnWindowResize));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it) {
			(*it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run() {
		ENGM_PROFILE_FUNCTION();

		while (m_Running) {
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized) {
				{
					ENGM_PROFILE_SCOPE("LayerStack::OnUpdate");

					for (Layer* layer : m_LayerStack)
						layer->OnUpdate(timestep);
				}
				m_ImGuiLayer->Begin();
				{
					ENGM_PROFILE_SCOPE("LayerStack::OnImGuiRender");

					for (Layer* layer : m_LayerStack)
						layer->OnImGuiRender();
					m_ImGuiLayer->End();
				}
				m_Window->OnUpdate();
			}
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e) {
		ENGM_PROFILE_FUNCTION();
	
		if (e.GetWidth() == 0 || e.GetHeight() == 0) {
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}
}
