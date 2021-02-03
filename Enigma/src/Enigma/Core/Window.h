#pragma once

#include "engmpch.h"

#include "Enigma/Core.h"
#include "Enigma/Events/Event.h"

namespace Enigma {

	struct WindowProperties {
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProperties(	const std::string& title = "Enigma Engine",
							uint32_t width = 1280,
							uint32_t height = 720)
			:Title(title), Width(width), Height(height) {}
	};

	//Enigma Engine Window Interface. NO DATA WHATSOEVER (also more for Desktops)
	class Window {
	public:
		using EventCallbackFunction = std::function<void(Event&)>;

		virtual ~Window() = default;
		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFunction& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Scope<Window> Create(const WindowProperties& props = WindowProperties());
	};

}
