#include "engmpch.h"
#include "WindowsInput.h"

#include "Enigma/Application.h"
#include <GLFW/glfw3.h>

namespace Enigma {

	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(KeyCode keycode) {
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, (int)keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	 bool WindowsInput::IsMouseButtonPressedImpl(MouseCode button) {
		 auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		 auto state = glfwGetMouseButton(window, (int)button);
		 return state == GLFW_PRESS;
	 }

	 std::pair<float, float> WindowsInput::GetMousePositionImpl() {
		 auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		 double xpos, ypos;
		 glfwGetCursorPos(window, &xpos, &ypos);
		 return { (float)xpos, (float)ypos };
	 }

	 float WindowsInput::GetMouseXImpl() {
		 return GetMousePositionImpl().first;
	 }

	 float WindowsInput::GetMouseYImpl() {
		 return GetMousePositionImpl().second;
	 }

}
