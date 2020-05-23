#pragma once

#include "Enigma/Core.h"


namespace Enigma {

	class ENIGMA_API Input {
	public:
		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		
		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;

		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	private:
		static Input* s_Instance;
	};

	typedef enum class MouseCode : uint16_t {
		Button0      = 0,
		Button1      = 1,
		Button2      = 2,
		Button3      = 3,
		Button4      = 4,
		Button5      = 5,
		Button6      = 6,
		Button7      = 7,
		ButtonLast   = Button7,
		ButtonLeft   = Button0,
		ButtonRight  = Button1,
		ButtonMiddle = Button2
	} Mouse ;

	inline std::ostream& operator<<(std::ostream& os, MouseCode code) {
		os << static_cast<int32_t>(code);
		return os;
	}

	typedef enum class KeyCode : uint16_t {
		Space        = 32,
		Apostrophe   = 39,
		Comma        = 44,
		Minus        = 45,
		Period       = 46,
		Slash        = 47,

		D0           = 48,  // 0
		D1           = 49,  // 1
		D2           = 50,  // 2
		D3           = 51,  // 3
		D4           = 52,  // 4
		D5           = 53,  // 5
		D6           = 54,  // 6
		D7           = 55,  // 7
		D8           = 56,  // 8
		D9           = 57,  // 9

		Semicolon    = 59,
		Equal        = 61,

		A            = 65,
		B            = 66,
		C            = 67,
		D            = 68,
		E            = 69,
		F            = 70,
		G            = 71,
		H            = 72,
		I            = 73,
		J            = 74,
		K            = 75,
		L            = 76,
		M            = 77,
		N            = 78,
		O            = 79,
		P            = 80,
		Q            = 81,
		R            = 82,
		S            = 83,
		T            = 84,
		U            = 85,
		V            = 86,
		W            = 87,
		X            = 88,
		Y            = 89,
		Z            = 90,

		LeftBracket  = 91,  // [
		Backslash    = 92,  /* \ */
		RightBracket = 93,  // ]
		GraveAccent  = 96,  // `

		World1       = 161, // non-US-like1
		World2       = 161, // non-US-like2

		Escape		 = 256,
		Enter		 = 257,
		Tab			 = 258,
		Backspace	 = 259,
		Insert		 = 260,
		Delete		 = 261,
		Right		 = 262,
		Left		 = 263,
		Down		 = 264,
		Up			 = 265,
		PageUp		 = 266,
		PadeDown	 = 267,
		Home		 = 268,
		End			 = 269,
		CapsLock	 = 280,
		ScrollLock	 = 281,
		NumLock		 = 282,
		PrintScreen  = 283,
		Pause        = 284,
		F1			 = 290,
		F2			 = 291,
		F3			 = 292,
		F4			 = 293,
		F5			 = 294,
		F6			 = 295,
		F7			 = 296,
		F8			 = 297,
		F9			 = 298,
		F10			 = 299,
		F11			 = 300,
		F12			 = 301,
		F13			 = 302,
		F14			 = 303,
		F15			 = 304,
		F16			 = 305,
		F17			 = 306,
		F18			 = 307,
		F19			 = 308,
		F20			 = 309,
		F21			 = 310,
		F22			 = 311,
		F23			 = 312,
		F24			 = 313,
		F25			 = 314,

		KP0          = 320,
		KP1          = 321,
		KP2          = 322,
		KP3          = 323,
		KP4          = 324,
		KP5          = 325,
		KP6          = 326,
		KP7          = 327,
		KP8          = 328,
		KP9          = 329,
		KPDecimal	 = 330,
		KPDivide	 = 331,
		KPMultiply	 = 332,
		KPSubtract   = 333,
		KPAdd		 = 334,
		KPEnter		 = 335,
		KPEqual      = 336,

		LeftShift    = 340,
		LeftControl	 = 341,
		LeftAlt		 = 342,
		LeftSuper	 = 343,
		RightShift	 = 344,
		RightControl = 345,
		RightAlt	 = 346,
		RightSuper	 = 347,
		Menu		 = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode code) {
		os << static_cast<int32_t>(code);
		return os;
	}

}

//from glfw3.h

//mouse
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

//keycodes
#define ENGM_KEY_SPACE           ::Enigma::Key::Space
#define ENGM_KEY_APOSTROPHE      ::Enigma::Key::Apostrophe    /* ' */
#define ENGM_KEY_COMMA           ::Enigma::Key::Comma         /* , */
#define ENGM_KEY_MINUS           ::Enigma::Key::Minus         /* - */
#define ENGM_KEY_PERIOD          ::Enigma::Key::Period        /* . */
#define ENGM_KEY_SLASH           ::Enigma::Key::Slash         /* / */
#define ENGM_KEY_0               ::Enigma::Key::D0
#define ENGM_KEY_1               ::Enigma::Key::D1
#define ENGM_KEY_2               ::Enigma::Key::D2
#define ENGM_KEY_3               ::Enigma::Key::D3
#define ENGM_KEY_4               ::Enigma::Key::D4
#define ENGM_KEY_5               ::Enigma::Key::D5
#define ENGM_KEY_6               ::Enigma::Key::D6
#define ENGM_KEY_7               ::Enigma::Key::D7
#define ENGM_KEY_8               ::Enigma::Key::D8
#define ENGM_KEY_9               ::Enigma::Key::D9
#define ENGM_KEY_SEMICOLON       ::Enigma::Key::Semicolon     /* ; */
#define ENGM_KEY_EQUAL           ::Enigma::Key::Equal         /* = */
#define ENGM_KEY_A               ::Enigma::Key::A
#define ENGM_KEY_B               ::Enigma::Key::B
#define ENGM_KEY_C               ::Enigma::Key::C
#define ENGM_KEY_D               ::Enigma::Key::D
#define ENGM_KEY_E               ::Enigma::Key::E
#define ENGM_KEY_F               ::Enigma::Key::F
#define ENGM_KEY_G               ::Enigma::Key::G
#define ENGM_KEY_H               ::Enigma::Key::H
#define ENGM_KEY_I               ::Enigma::Key::I
#define ENGM_KEY_J               ::Enigma::Key::J
#define ENGM_KEY_K               ::Enigma::Key::K
#define ENGM_KEY_L               ::Enigma::Key::L
#define ENGM_KEY_M               ::Enigma::Key::M
#define ENGM_KEY_N               ::Enigma::Key::N
#define ENGM_KEY_O               ::Enigma::Key::O
#define ENGM_KEY_P               ::Enigma::Key::P
#define ENGM_KEY_Q               ::Enigma::Key::Q
#define ENGM_KEY_R               ::Enigma::Key::R
#define ENGM_KEY_S               ::Enigma::Key::S
#define ENGM_KEY_T               ::Enigma::Key::T
#define ENGM_KEY_U               ::Enigma::Key::U
#define ENGM_KEY_V               ::Enigma::Key::V
#define ENGM_KEY_W               ::Enigma::Key::W
#define ENGM_KEY_X               ::Enigma::Key::X
#define ENGM_KEY_Y               ::Enigma::Key::Y
#define ENGM_KEY_Z               ::Enigma::Key::Z
#define ENGM_KEY_LEFT_BRACKET    ::Enigma::Key::LeftBracket   /* [ */
#define ENGM_KEY_BACKSLASH       ::Enigma::Key::Backslash     /* \ */
#define ENGM_KEY_RIGHT_BRACKET   ::Enigma::Key::RightBracket  /* ] */
#define ENGM_KEY_GRAVE_ACCENT    ::Enigma::Key::GraveAccent   /* ` */
#define ENGM_KEY_WORLD_1         ::Enigma::Key::World1        /* non-US #1 */
#define ENGM_KEY_WORLD_2         ::Enigma::Key::World2        /* non-US #2 */

/* Function keys */
#define ENGM_KEY_ESCAPE          ::Enigma::Key::Escape
#define ENGM_KEY_ENTER           ::Enigma::Key::Enter
#define ENGM_KEY_TAB             ::Enigma::Key::Tab
#define ENGM_KEY_BACKSPACE       ::Enigma::Key::Backspace
#define ENGM_KEY_INSERT          ::Enigma::Key::Insert
#define ENGM_KEY_DELETE          ::Enigma::Key::Delete
#define ENGM_KEY_RIGHT           ::Enigma::Key::Right
#define ENGM_KEY_LEFT            ::Enigma::Key::Left
#define ENGM_KEY_DOWN            ::Enigma::Key::Down
#define ENGM_KEY_UP              ::Enigma::Key::Up
#define ENGM_KEY_PAGE_UP         ::Enigma::Key::PageUp
#define ENGM_KEY_PAGE_DOWN       ::Enigma::Key::PageDown
#define ENGM_KEY_HOME            ::Enigma::Key::Home
#define ENGM_KEY_END             ::Enigma::Key::End
#define ENGM_KEY_CAPS_LOCK       ::Enigma::Key::CapsLock
#define ENGM_KEY_SCROLL_LOCK     ::Enigma::Key::ScrollLock
#define ENGM_KEY_NUM_LOCK        ::Enigma::Key::NumLock
#define ENGM_KEY_PRINT_SCREEN    ::Enigma::Key::PrintScreen
#define ENGM_KEY_PAUSE           ::Enigma::Key::Pause
#define ENGM_KEY_F1              ::Enigma::Key::F1
#define ENGM_KEY_F2              ::Enigma::Key::F2
#define ENGM_KEY_F3              ::Enigma::Key::F3
#define ENGM_KEY_F4              ::Enigma::Key::F4
#define ENGM_KEY_F5              ::Enigma::Key::F5
#define ENGM_KEY_F6              ::Enigma::Key::F6
#define ENGM_KEY_F7              ::Enigma::Key::F7
#define ENGM_KEY_F8              ::Enigma::Key::F8
#define ENGM_KEY_F9              ::Enigma::Key::F9
#define ENGM_KEY_F10             ::Enigma::Key::F10
#define ENGM_KEY_F11             ::Enigma::Key::F11
#define ENGM_KEY_F12             ::Enigma::Key::F12
#define ENGM_KEY_F13             ::Enigma::Key::F13
#define ENGM_KEY_F14             ::Enigma::Key::F14
#define ENGM_KEY_F15             ::Enigma::Key::F15
#define ENGM_KEY_F16             ::Enigma::Key::F16
#define ENGM_KEY_F17             ::Enigma::Key::F17
#define ENGM_KEY_F18             ::Enigma::Key::F18
#define ENGM_KEY_F19             ::Enigma::Key::F19
#define ENGM_KEY_F20             ::Enigma::Key::F20
#define ENGM_KEY_F21             ::Enigma::Key::F21
#define ENGM_KEY_F22             ::Enigma::Key::F22
#define ENGM_KEY_F23             ::Enigma::Key::F23
#define ENGM_KEY_F24             ::Enigma::Key::F24
#define ENGM_KEY_F25             ::Enigma::Key::F25

/* Keypad */
#define ENGM_KEY_KP_0            ::Enigma::Key::KP0
#define ENGM_KEY_KP_1            ::Enigma::Key::KP1
#define ENGM_KEY_KP_2            ::Enigma::Key::KP2
#define ENGM_KEY_KP_3            ::Enigma::Key::KP3
#define ENGM_KEY_KP_4            ::Enigma::Key::KP4
#define ENGM_KEY_KP_5            ::Enigma::Key::KP5
#define ENGM_KEY_KP_6            ::Enigma::Key::KP6
#define ENGM_KEY_KP_7            ::Enigma::Key::KP7
#define ENGM_KEY_KP_8            ::Enigma::Key::KP8
#define ENGM_KEY_KP_9            ::Enigma::Key::KP9
#define ENGM_KEY_KP_DECIMAL      ::Enigma::Key::KPDecimal
#define ENGM_KEY_KP_DIVIDE       ::Enigma::Key::KPDivide
#define ENGM_KEY_KP_MULTIPLY     ::Enigma::Key::KPMultiply
#define ENGM_KEY_KP_SUBTRACT     ::Enigma::Key::KPSubtract
#define ENGM_KEY_KP_ADD          ::Enigma::Key::KPAdd
#define ENGM_KEY_KP_ENTER        ::Enigma::Key::KPEnter
#define ENGM_KEY_KP_EQUAL        ::Enigma::Key::KPEqual

#define ENGM_KEY_LEFT_SHIFT      ::Enigma::Key::LeftShift
#define ENGM_KEY_LEFT_CONTROL    ::Enigma::Key::LeftControl
#define ENGM_KEY_LEFT_ALT        ::Enigma::Key::LeftAlt
#define ENGM_KEY_LEFT_SUPER      ::Enigma::Key::LeftSuper		/*Windows Key*/
#define ENGM_KEY_RIGHT_SHIFT     ::Enigma::Key::RightShift
#define ENGM_KEY_RIGHT_CONTROL   ::Enigma::Key::RightControl
#define ENGM_KEY_RIGHT_ALT       ::Enigma::Key::RightAlt
#define ENGM_KEY_RIGHT_SUPER     ::Enigma::Key::RightSuper		/*Windows Key*/
#define ENGM_KEY_MENU            ::Enigma::Key::Menu
