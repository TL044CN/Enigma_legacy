#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Enigma {

	class ENIGMA_API Log {
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
		static std::shared_ptr<spdlog::logger> s_CoreLogger;

	};

}

#ifdef ENGM_DEBUG

//Core logging macros
//	#define ENGM_CORE_FATAL(...)     ::Enigma::Log::GetCoreLogger()->fatal(__VA_ARGS__)
	#define ENGM_CORE_ERROR(...)     ::Enigma::Log::GetCoreLogger()->error(__VA_ARGS__)
	#define ENGM_CORE_WARN(...)      ::Enigma::Log::GetCoreLogger()->warn(__VA_ARGS__)
	#define ENGM_CORE_INFO(...)      ::Enigma::Log::GetCoreLogger()->info(__VA_ARGS__)
	#define ENGM_CORE_TRACE(...)     ::Enigma::Log::GetCoreLogger()->trace(__VA_ARGS__)

//Client logging macros
//	#define ENGM_Client_FATAL(...)   ::Enigma::Log::GetClientLogger()->fatal(__VA_ARGS__)
	#define ENGM_CLIENT_ERROR(...)   ::Enigma::Log::GetClientLogger()->error(__VA_ARGS__)
	#define ENGM_CLIENT_WARN(...)    ::Enigma::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define ENGM_CLIENT_INFO(...)    ::Enigma::Log::GetClientLogger()->info(__VA_ARGS__)
	#define ENGM_CLIENT_TRACE(...)   ::Enigma::Log::GetClientLogger()->trace(__VA_ARGS__)

#else
	//Core logging macros
//	#define ENGM_CORE_FATAL(...)
	#define ENGM_CORE_ERROR(...)
	#define ENGM_CORE_WARN(...)
	#define ENGM_CORE_INFO(...)
	#define ENGM_CORE_TRACE(...)

	//Client logging macros
//	#define ENGM_Client_FATAL(...)
	#define ENGM_CLIENT_ERROR(...)
	#define ENGM_CLIENT_WARN(...)
	#define ENGM_CLIENT_INFO(...)
	#define ENGM_CLIENT_TRACE(...)
#endif
