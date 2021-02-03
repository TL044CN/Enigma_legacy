#pragma once

#include "Enigma/Core.h"
#include "Enigma/Core/Keycodes.h"
#include "Enigma/Core/MouseCodes.h"

namespace Enigma {

	class Input {
	public:
		//Check if the specified Key is pressed
		static bool IsKeyPressed(KeyCode key);

		//Checks if the specified Mouse Button is pressed
		static bool IsMouseButtonPressed(MouseCode button);
		//returns the current Mouse Position as a std::pair<x,y>
		static std::pair<float, float> GetMousePosition();
		//returns the current Mouse X Position
		static float GetMouseX();
		//returns the current Mouse Y Position
		static float GetMouseY();
	};

}
