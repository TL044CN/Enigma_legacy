#pragma once
#include "Event.h"

#if defined(ENGM_DEBUG) || defined(ENGM_RELEASE)
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

	class KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(int keycode, int repeatCount) : KeyEvent(keycode), m_RepeatCount(repeatCount) {}
		int GetRepearCount() const { return m_RepeatCount; };

#if defined(ENGM_DEBUG) || defined(ENGM_RELEASE)
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

	class KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

#if defined(ENGM_DEBUG) || defined(ENGM_RELEASE)
		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}
#endif

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class KeyTypedEvent : public KeyEvent {
	public:
		KeyTypedEvent(int keycode) :KeyEvent(keycode) {}

#if defined(ENGM_DEBUG) || defined(ENGM_RELEASE)
		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}
#endif

		EVENT_CLASS_TYPE(KeyTyped)
	};

}
