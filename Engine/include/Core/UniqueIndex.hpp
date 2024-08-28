#pragma once

#include <inttypes.h>
#include <stack>

namespace eng {

typedef uint64_t Index;
constexpr Index UNVALID = 0xffffffffffffffff;

class UniqueIndex {
public:
    UniqueIndex();

    operator Index();

private:
    Index m_index;

    static Index s_track;
};

uint64_t get_unique() {
    static uint64_t s_current(0);
    ++s_current;
    return s_current;
}

}