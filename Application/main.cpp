#include <iostream>

#include "Engine.hpp"
#include "Test.hpp"

int main(int argc, char** args) {
    std::cout << "Hello World" << std::endl;

    eng::_ENGINE_TEST_ eng(3);
    std::cout << eng.GetValue() << std::endl;

    test_function('x', 12);

    return 0;
}