#pragma once

#include <iostream>

namespace eng {

class _ENGINE_TEST_ {
public:
    _ENGINE_TEST_(int value);

    int GetValue();

    void SetValue(int value); 

private:
    int m_value;
};

}