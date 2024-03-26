#include "Core/UniqueIndex.hpp"

namespace eng {

Index UniqueIndex::s_track = 0;

UniqueIndex::UniqueIndex()
: m_index(s_track++)
{}

UniqueIndex::operator Index() {
    return m_index;
}

}