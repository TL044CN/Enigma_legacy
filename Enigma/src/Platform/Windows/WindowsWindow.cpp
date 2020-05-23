#include "engmpch.h"
#include "WindowsWindow.h"

#include "Enigma/Events/ApplicationEvent.h"
#include "Enigma/Events/KeyEvent.h"
#include "Enigma/Events/MouseEvent.h"

#include <glad/glad.h>

namespace Enigma {

	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description) {
		ENGM_CORE_ERROR("GLFW Error: [{0}]: {1}", error, description);
	}

	Window* Window::Create(const WindowProperties& props) {
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProperties& props) {
		Init(props);
	}

	WindowsWindow::~WindowsWindow() {
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProperties& props) {
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		ENGM_CORE_INFO("Atteppt at creating Window {0} ({1}x{2})",m_Data.Title, m_Data.Width,m_Data.Height);

		if (!s_GLFWInitialized) {
			int success = glfwInit();
			ENGM_CORE_ASSERT(success,"could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ENGM_CORE_ASSERT(status, "Failed to initialize Glad!");

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		//Callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetWindowFocusCallback(m_Window, [](GLFWwindow* window, int focus) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (focus) {
				case GLFW_TRUE: {
					WindowFocusEvent event;
					data.EventCallback(event);
					break;
				}
				case GLFW_FALSE: {
					WindowFocusLostEvent event;
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action) {
				case GLFW_PRESS: {
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT: {
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE: {
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break; 
				}
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int charcode) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent event(charcode);
			data.EventCallback(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
				case GLFW_PRESS: {
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break; 
				}
				case GLFW_RELEASE: {
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double x, double y ) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent event((float)x, (float)y);
			data.EventCallback(event);
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double v, double h) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent event((float)v, (float)h);
			data.EventCallback(event);
		});

	}

	void WindowsWindow::Shutdown() {
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled) {
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const {
		return m_Data.VSync;
	}

}