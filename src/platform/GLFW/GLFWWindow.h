#ifndef ELIGMA_GLFWWINDOW_H
#define ELIGMA_GLFWWINDOW_H

#include "../../Core/Window.h"
#include <GLFW/glfw3.h>

namespace Enigma {
    class WindowsWindow : public Window {
    private:
        GLFWwindow* mWindow;

        struct WindowData {
            std::string Title;
            uint32_t Width, Height;
            bool VSync;
            EventCallbackFunction EventCallback;
        };

    public:
        WindowsWindow(const WindowProperties& props);
        virtual ~WindowsWindow();

    private:
        virtual void Init(const WindowProperties& props);
        virtual void Shutdown();

    public:
        virtual void onUpdate();

        virtual uint32_t getWidth() const;
        virtual uint32_t getHeight() const;

        virtual void setEventCallback(const Window::EventCallbackFunction& cb);
        virtual void setVSync(bool enabled = 1);
        virtual bool isVSync() const;

        virtual void* getNativeWindow() const;
    private:

    };
}

#endif