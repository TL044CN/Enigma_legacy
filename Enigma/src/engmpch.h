#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <functional>
#include <algorithm>

#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <unordered_map>
#include <unordered_set>

#include "Enigma/Core/Log.h"
#include "Enigma/Debug/Profiler.h"

#ifdef ENGM_PLATFORM_WINDOWS
	#include <Windows.h>
#endif

#define STB_IMAGE_IMPLEMENTATION
