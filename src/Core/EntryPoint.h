#ifndef TTENIGMA_ENTRYPOINT_H
#define TTENIGMA_ENTRYPOINT_H

#include "Core.h"
#include "Application.h"

extern Enigma::Application* Enigma::createApplication();

int main(int argc, char** argv) {
//    Enigma::Log::Init();
    ENGM_PROFILE_BEGIN_SESSION("Startup", "EnigmaProfile-Startup.json");
    auto app = Enigma::createApplication();
    ENGM_PROFILE_END_SESSION();

    ENGM_PROFILE_BEGIN_SESSION("Runtime", "EnigmaProfile-Runtime.json");
    app->run();
    ENGM_PROFILE_END_SESSION();

    ENGM_PROFILE_BEGIN_SESSION("Shutdown", "EnigmaProfile-Shutdown.json");
    delete app;
    ENGM_PROFILE_END_SESSION();
}

#endif