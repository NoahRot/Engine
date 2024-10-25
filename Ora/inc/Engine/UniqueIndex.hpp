#pragma once

#include <inttypes.h>

namespace ora {

typedef uint64_t Index;

constexpr uint32_t UNVALID_32 = 0xffff;
constexpr uint64_t UNVALID_64 = 0xffffffff;

Index get_unique();

}