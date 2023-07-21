#ifndef TTENIGMA_EVENT_H
#define TTENIGMA_EVENT_H

#include "../Core/Core.h"
#include <cstdint>
#include <functional>

namespace Enigma {

    enum class EventType {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowFocusLost, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyUp, KeyDown, KeyHeld,
        MouseDown, MouseUp, MouseMove, MouseScroll
    };

    enum class EventCategory {
        None = 0,
        Application = 0x1,
        Input = 0x2,
        Keyboard = 0x4,
        Mouse = 0x8,
        MouseButton = 0x10
    };

#define EVT_CLASS_TYPE(type)\
    static EventType getStaticType() { return EventType::type; }\
    virtual EventType getEventType() const override {return getStaticType(); }\
    virtual const char* getName() const override { return #type; }

#define EVT_CLASS_CATEGORY(cat)\
    virtual uint32_t getCategoryFlags() const override { return static_cast<uint32_t>(cat); }

    class Event {
    public:
        bool handled = false;
        
        virtual EventType getEventType() const = 0;
        virtual const char* getName() const = 0;
        virtual uint32_t getCategoryFlags() const = 0;
        inline virtual std::string toString() const { return getName(); }

        inline bool isInCategory(EventCategory category) {
            return getCategoryFlags() & static_cast<uint32_t>(category);
        }

        inline static EventType getStaticType() { return EventType::None; }
    };

    class EventDispatcher{
    private:
        template<typename T> using EvtFn = std::function<bool(T&)>;
        
    private:
        Event& mEvent;

    public:
        EventDispatcher(Event& event) : mEvent(event) {}

    public:

        template<typename EVT>
        bool dispatch(EvtFn<EVT> fn){
            if(mEvent.getEventType() == EVT::getStaticType()){
                mEvent.handled = fn(*(EVT*)&mEvent);
                return true;
            }
            return false;
        }

    };

    inline std::ostream& operator<<(std::ostream& stream, const Event& e){
        return stream << e.toString();
    }

}

#endif