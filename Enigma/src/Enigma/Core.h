#pragma once

#ifdef ENGM_PLATFORM_WINDOWS
#if ENGM_DYNAMIC_LINK
	#ifdef ENGM_BUILD_DLL
		#define ENIGMA_API __declspec(dllexport)
	#else
		#define ENIGMA_API __declspec(dllimport)
	#endif

	#ifdef ENGM_DEBUG
		#define ENGM_ENABLE_ASSERT
	#endif
#else
#define ENIGMA_API
#endif
#else
	#error Enigma Engine only supports Windows (for now)
#endif

#define ENGM_BIND_EVENT_FUNCTION(function) std::bind(&function, this, std::placeholders::_1)
