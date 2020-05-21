#pragma once
#include "Event.h"

#ifdef ENGM_DEBUG or ENGM_RELEASE
#include <sstream>
#endif

namespace Enigma {

	class KeyEvent : public Event {
	public:
		int GetKeycode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		KeyEvent(int keycode) :m_KeyCode(keycode) {}
		int m_KeyCode;
	};

	class ENIGMA_API KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(int keycode, int repeatCount) : KeyEvent(keycode), m_RepeatCount(repeatCount) {}
		int GetRepearCount() const { return m_RepeatCount; };

#ifdef ENGM_DEBUG or ENGM_RELEASE
		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}
#endif

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};

	class ENIGMA_API KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

#ifdef ENGM_DEBUG or ENGM_RELEASE
		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}
#endif

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class ENIGMA_API KeyTypedEvent : public KeyEvent {
	public:
		KeyTypedEvent(int keycode) :KeyEvent(keycode) {}

#ifdef ENGM_DEBUG or ENGM_RELEASE
		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}
#endif

		EVENT_CLASS_TYPE(KeyTyped)
	};

}
