#include <iostream>

#include "Engine.hpp"

int main(int argc, char** args) {
    std::cout << "HELLO WORLD" << std::endl;

    eng::log::Logger logger(100);

    logger.CreateDisplayer<eng::log::LogDisplayerCMD>();
    logger.CreateDisplayer<eng::log::LogDisplayerTXT>("../Engine.log");

    logger.Info("Main", "Program started");

    eng::Window  window;

    logger.Info("Main", "Program ended");


    return 0;
}