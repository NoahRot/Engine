#include <iostream>

#include "Engine.hpp"
#include "Core/Configuration.hpp"

int main(int argc, char** args) {

    eng::Configuration config;
    config.log_displayTXT = true;
    config.log_displayTXTName = "../Engine.log";

    eng::Configure(config);

    eng::Configure(config);

    eng::log::Logger& logger = eng::log::Logger::Instance();

    logger.Info("Main", "Program started");

    logger.Info("Main", "Program ended");

    return 0;
}