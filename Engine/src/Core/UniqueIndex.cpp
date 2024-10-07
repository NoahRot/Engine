#include "Core/UniqueIndex.hpp"

namespace eng {

Index UniqueIndex::s_track = 0;

UniqueIndex::UniqueIndex()
: m_index(s_track++)
{}

UniqueIndex::operator Index() {
    return m_index;
}

Index get_unique() {
    static uint64_t s_current(0);
    ++s_current;
    return s_current;
}

}