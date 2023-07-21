#include "Application.h"

namespace Enigma {

    Application* Application::sInstance = nullptr;

    Application::Application(const std::string& name){
        ENGM_PROFILE_FUNCTION();

        if(sInstance) return;
        sInstance = this;

        mWindow = Window::Create(WindowProperties(name));
        mWindow->setEventCallback(ENIGMA_BIND_EVT_FN(Application::onEvent));

    }

    Application::~Application(){
        ENGM_PROFILE_FUNCTION();        
    }


    bool Application::onWindowClose(WindowCloseEvent& event){
        mRunning = false;
        return true;
    }

    bool Application::onWindowResize(WindowResizeEvent& event){
        ENGM_PROFILE_FUNCTION();

        if(event.getWidth() == 0 || event.getHeight() == 0){
            mMinimized = true;
            return false;
        }

        mMinimized = false;

        return false;
    }

    void Application::close() {
        mRunning = false;
    }

    void Application::run(){
        ENGM_PROFILE_FUNCTION();
        while(mRunning){
            float time = (float)glfwGetTime();
            auto ts = time - mLastFrameTime;
            mLastFrameTime = time;

            if(mMinimized) continue;

            mWindow->onUpdate();
        }
    }

    void Application::onEvent(Event& event){
        ENGM_PROFILE_FUNCTION();

        EventDispatcher dispatcher(event);
        dispatcher.dispatch<WindowCloseEvent>(ENIGMA_BIND_EVT_FN(Application::onWindowClose));
        dispatcher.dispatch<WindowResizeEvent>(ENIGMA_BIND_EVT_FN(Application::onWindowResize));

    }

}