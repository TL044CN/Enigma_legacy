#ifndef TTENIGMA_APPLICATION_EVENTS_H
#define TTENIGMA_APPLICATION_EVENTS_H

#include "Event.h"
#include <sstream>

namespace Enigma {
    class WindowResizeEvent : public Event {
    private:
        uint32_t mWidth, mHeight;

    public:
        WindowResizeEvent(uint32_t width, uint32_t height)
        : mWidth(width), mHeight(height) {}

        inline uint32_t getWidth() const { return mWidth; }
        inline uint32_t getHeight() const { return mHeight; }

        std::string toString() const override {
            std::stringstream ss;
            ss << "Window Resize Event: " << mWidth << ", " << mHeight;
            return ss.str();
        }

        EVT_CLASS_TYPE(WindowResize)
        EVT_CLASS_CATEGORY(EventCategory::Application)
    };

    class WindowCloseEvent : public Event {
    public:
        WindowCloseEvent() = default;

        EVT_CLASS_TYPE(WindowClose)
        EVT_CLASS_CATEGORY(EventCategory::Application)
    };

    class WindowFocusEvent : public Event {
    public:
        WindowFocusEvent() = default;

        EVT_CLASS_TYPE(WindowFocus)
        EVT_CLASS_CATEGORY(EventCategory::Application)
    };

    class WindowFocusLostEvent : public Event {
    public:
        WindowFocusLostEvent() = default;

        EVT_CLASS_TYPE(WindowFocusLost)
        EVT_CLASS_CATEGORY(EventCategory::Application)
    };    

    class AppTickEvent : public Event {
    public:
        AppTickEvent() = default;

        EVT_CLASS_TYPE(AppTick)
        EVT_CLASS_CATEGORY(EventCategory::Application)
    };

    class AppUpdateEvent : public Event {
    public:
        AppUpdateEvent() = default;

        EVT_CLASS_TYPE(AppUpdate)
        EVT_CLASS_CATEGORY(EventCategory::Application)
    };

    class AppRenderEvent : public Event {
    public:
        AppRenderEvent() = default;

        EVT_CLASS_TYPE(AppRender)
        EVT_CLASS_CATEGORY(EventCategory::Application)
    };    

}

#endif