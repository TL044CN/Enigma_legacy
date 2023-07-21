#ifndef TTENIGMA_APPLICATION_H
#define TTENIGMA_APPLICATION_H

#include "Core.h"
#include "Window.h"
#include "../Event/ApplicationEvents.h"

#include <GLFW/glfw3.h>
#include <memory>

namespace Enigma {

    class Application {
    private:
        static Application* sInstance;
        
        bool mRunning = true;
        bool mMinimized = false;
        double mLastFrameTime = 0.0;

        std::unique_ptr<Window> mWindow;

        bool onWindowClose(WindowCloseEvent& event);
        bool onWindowResize(WindowResizeEvent& event);
    
    public:
        Application(const std::string& name = "Enigma Engine");
        virtual ~Application();

    public:
        void run();
        void onEvent(Event& event);
        void close();

        Window* getWindow();

        inline static Application& get() { return *sInstance; }
    };

    Application* createApplication();

}

#endif