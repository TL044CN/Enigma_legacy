#include "Log.h"
#include <iostream>

namespace Enigma {
    std::shared_ptr<Logger> Log::sCoreLogger;
    std::shared_ptr<Logger> Log::sClientLogger;

    void Log::Init(){
        sClientLogger = std::make_shared<Logger>(std::cout, "Client");
        sCoreLogger = std::make_shared<Logger>(std::cout, "Core");
    }

}
