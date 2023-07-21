#ifndef TTENIGMA_WINDOW_H
#define TTENIGMA_WINDOW_H

#include "Core.h"
#include "../Event/Event.h"
#include <functional>

namespace Enigma {
    struct WindowProperties {
        std::string title;
        uint32_t width, height;

        WindowProperties(
            const std::string& _title = "Enigma Engine",
            uint32_t _width = 1080, uint32_t _height = 720
        ) : title(_title), width(_width), height(_height) {}
    };

    class Window {
    public:
        using EventCallbackFunction = std::function<void(Event&)>;

    public:
        virtual ~Window() = default;
        virtual void onUpdate() = 0;

        virtual uint32_t getWidth() const = 0;
        virtual uint32_t getHeight() const = 0;

        virtual void setEventCallback(const EventCallbackFunction& cb) = 0;
        virtual void setVSync(bool enabled = 1) = 0;
        virtual bool isVSync() const = 0;

        virtual void* getNativeWindow() const = 0;

    public:
        static std::unique_ptr<Window> Create(
            const WindowProperties& props = WindowProperties()
        );
    };
} 

#endif