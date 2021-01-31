#pragma once
#include <memory>

#ifdef ENGM_PLATFORM_WINDOWS

#else
	#error Enigma Engine only supports Windows (for now)
#endif

#define ENGM_BIND_EVENT_FUNCTION(function) std::bind(&function, this, std::placeholders::_1)

#ifdef ENGM_DEBUG
	#define ENGM_ENABLE_ASSERTS
#endif

namespace Enigma {

	//Abstracting away Smart Pointers into Scoped and Referenced Pointers

	template <typename T>
	using Scope = std::unique_ptr<T>;
	template <typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template <typename T>
	using Ref = std::shared_ptr<T>;
	template <typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args) {
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}