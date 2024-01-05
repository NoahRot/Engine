#include "Engine.hpp"

namespace eng {

_ENGINE_TEST_::_ENGINE_TEST_(int value)
: m_value(value)
{
    std::cout << "Hello Engine" << std::endl;
}

int _ENGINE_TEST_::GetValue() {
    return m_value;
}

void _ENGINE_TEST_::SetValue(int value) {
    m_value = value;
}

}