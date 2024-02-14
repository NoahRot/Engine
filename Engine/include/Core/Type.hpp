#pragma once

#include <inttypes.h>

namespace eng {

#ifdef ENG_INDEX_32
typedef uint32_t Index;
#else
typedef uint16_t Index;
#endif


constexpr Index UNVALID = 0xffff;

}