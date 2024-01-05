#include "Test.hpp"

void test_function(char c, int nbr) {
    for(int i(0) ; i < nbr ; ++i) {
        std::cout << c;
    }
    std::cout << std::endl;
}