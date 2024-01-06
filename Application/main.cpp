#include <iostream>

#include "Engine.hpp"

int main(int argc, char** args) {
    std::cout << "Hello World" << std::endl;

    eng::log::Logger logger(100);

    logger.CreateDisplayer<eng::log::LogDisplayerCMD>();
    logger.CreateDisplayer<eng::log::LogDisplayerTXT>("Engine.log");

    logger.SetDisplayType(eng::log::Debug, false);

    logger.Info("Main", "Info test");
    logger.Warning("Main", "Warning test");
    logger.Debug("Main", "Debug test");
    logger.Error("Main", "Error test");
    logger.Fatal("Main", "Fatal test");

    eng::Window win;

    return 0;
}