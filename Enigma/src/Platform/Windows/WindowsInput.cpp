#include "engmpch.h"
#include "Enigma/Core/Input.h"

#include "Enigma/Core/Application.h"
#include <GLFW/glfw3.h>

namespace Enigma {

	//Checks if the specified Keyboard Key is pressed
	bool Input::IsKeyPressed(KeyCode key) {
		//Get the current Window as a GLFWwindow to use with GLFW
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		//get the State of the Key then return the Check (if it was pressed or is held)
		auto state = glfwGetKey(window, static_cast<int32_t>(key));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	//Checks if the specified Mouse Button is pressed
	bool Input::IsMouseButtonPressed(MouseCode button) {
		//Get the current Window as a GLFWwindow to use with GLFW
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		//get the State of the Button then return the Check (if it was pressed)
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
		return state == GLFW_PRESS;
	}

	//returns the Current MousePosition. Not Implemented yet
	std::pair<float, float> Input::GetMousePosition() {
		//Get the current Window as a GLFWwindow to use with GLFW
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		double xpos, ypos;
		return { (float)xpos,(float)ypos };
	}

	//Not Implemented Yet
	float Input::GetMouseX() {
		auto [x, y] = GetMousePosition();
		return x;
	}

	//Not Implemented Yet
	float Input::GetMouseY() {
		auto [x, y] = GetMousePosition();
		return y;
	}
}
