#pragma once

#include <cstdint>
#include <ostream>

namespace Enigma {

	typedef enum class MouseCode : uint16_t {
		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Button6 = 6,
		Button7 = 7,
		ButtonLast = Button7,
		ButtonLeft = Button0,
		ButtonRight = Button1,
		ButtonMiddle = Button2
	} Mouse;

	inline std::ostream& operator<<(std::ostream& os, MouseCode code) {
		os << static_cast<int32_t>(code);
		return os;
	}

}

#define ENGM_MOUSE_BUTTON_0      ::Enigma::Mouse::Button0
#define ENGM_MOUSE_BUTTON_1      ::Enigma::Mouse::Button1
#define ENGM_MOUSE_BUTTON_2      ::Enigma::Mouse::Button2
#define ENGM_MOUSE_BUTTON_3      ::Enigma::Mouse::Button3
#define ENGM_MOUSE_BUTTON_4      ::Enigma::Mouse::Button4
#define ENGM_MOUSE_BUTTON_5      ::Enigma::Mouse::Button5
#define ENGM_MOUSE_BUTTON_6      ::Enigma::Mouse::Button6
#define ENGM_MOUSE_BUTTON_7      ::Enigma::Mouse::Button7
#define ENGM_MOUSE_BUTTON_LAST   ::Enigma::Mouse::ButtonLast
#define ENGM_MOUSE_BUTTON_LEFT   ::Enigma::Mouse::ButtonLeft
#define ENGM_MOUSE_BUTTON_RIGHT  ::Enigma::Mouse::ButtonRight
#define ENGM_MOUSE_BUTTON_MIDDLE ::Enigma::Mouse::ButtonMiddle
