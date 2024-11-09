#pragma once

#include <inttypes.h>

namespace ora {

typedef uint64_t Index;

constexpr uint32_t UNVALID_32 = 0xffffffff;
constexpr uint64_t UNVALID_64 = 0xffffffffffffffff;

Index get_unique();

}