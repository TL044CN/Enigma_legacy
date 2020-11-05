#pragma once
#include <memory>

#ifdef ENGM_PLATFORM_WINDOWS

#else
	#error Enigma Engine only supports Windows (for now)
#endif

#define ENGM_BIND_EVENT_FUNCTION(function) std::bind(&function, this, std::placeholders::_1)

namespace Enigma {
	template <typename T>
	using Scope = std::unique_ptr<T>;

	template <typename T>
	using Ref = std::shared_ptr<T>;
}