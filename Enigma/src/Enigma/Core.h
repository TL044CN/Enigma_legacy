#pragma once

#ifdef ENGM_PLATFORM_WINDOWS

#else
	#error Enigma Engine only supports Windows (for now)
#endif

#define ENGM_BIND_EVENT_FUNCTION(function) std::bind(&function, this, std::placeholders::_1)
