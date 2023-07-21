#ifndef TTENIGMLOG_H
#define TTENIGMLOG_H

#include "Logger.h"
#include <memory>

namespace Enigma {
    
    class Log {
    private:
        static std::shared_ptr<Logger> sClientLogger;
        static std::shared_ptr<Logger> sCoreLogger;

    public:
        static void Init();

        inline static std::shared_ptr<Logger>& getClientLogger() { return sClientLogger; }
        inline static std::shared_ptr<Logger>& getCoreLogger() { return sCoreLogger; }

    };

}


#if ENIGMA_LOGGER
#define ENIGMA_FATAL(...) ::Enigma::Log::GetClientLogger()->fatal(__VA_ARGS__)
#define ENIGMA_ERROR(...) ::Enigma::Log::GetClientLogger()->error(__VA_ARGS__)
#define ENIGMA_WARN(...) ::Enigma::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ENIGMA_INFO(...) ::Enigma::Log::GetClientLogger()->info(__VA_ARGS__)
#define ENIGMA_TRACE(...) ::Enigma::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ENIGMA_CORE_FATAL(...) ::Enigma::Log::GetCoreLogger()->fatal(__VA_ARGS__)
#define ENIGMA_CORE_ERROR(...) ::Enigma::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ENIGMA_CORE_WARN(...) ::Enigma::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ENIGMA_CORE_INFO(...) ::Enigma::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ENIGMA_CORE_TRACE(...) ::Enigma::Log::GetCoreLogger()->trace(__VA_ARGS__)
#else
#define ENIGMA_FATAL(...)
#define ENIGMA_ERROR(...)
#define ENIGMA_WARN(...)
#define ENIGMA_INFO(...)
#define ENIGMA_TRACE(...)
#define ENIGMA_CORE_FATAL(...)
#define ENIGMA_CORE_ERROR(...)
#define ENIGMA_CORE_WARN(...)
#define ENIGMA_CORE_INFO(...)
#define ENIGMA_CORE_TRACE(...)
#endif
#if ENIGMA_ENABLE_ASSERT
#define ENIGMA_ASSERT(contition,...)\
if(!condition){\
    ::Enigma::Log::GetClientLogger()->fatal(__VA_ARGS__);\
}
#define ENIGMA_CORE_ASSERT(contition,...)\
if(!condition){\
    ::Enigma::Log::GetCoreLogger()->fatal(__VA_ARGS__);\
}
#else
#define ENIGMA_ASSERT(contition,...)
#define ENIGMA_CORE_ASSERT(contition,...)
#endif
#endif