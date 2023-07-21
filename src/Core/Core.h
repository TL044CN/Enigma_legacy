#ifndef TTENIGMA_CORE_H
#define TTENIGMA_CORE_H

#include <memory>
#include "../debug/Profiler.h"

#define ENIGMA_BIND_EVT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#endif