#include <iostream>

#define ENG_LOG_THREAD

#include "Logger/Log.hpp"
#include "Core/Window_.hpp"
#include "Core/Initialization.hpp"

#include <cmath>

#include <random>
#include <chrono>

void test_logger(eng::Logger& logger) {
    logger.log(eng::FATAL, "Test FATAL");
    logger.log(eng::ERROR, "Test ERROR");
    logger.log(eng::WARNING, "Test WARNING");
    logger.log(eng::INFO, "Test INFO");
    logger.log(eng::DEBUG, "Test DEBUG");
    logger.log(eng::TRACE, "Test TRACE");
}

int main(int argc, char* argv[]) {
    std::cout << "Begin program" << std::endl;

    eng::Logger logger;
    if (logger.init(true, false, "log_file")) {
        test_logger(logger);
    }else{
        std::cout << "FATAL::Can not init logger" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (!eng::init(&logger)) {
        logger.log(eng::FATAL, "Can not initialize ENGINE");
        exit(EXIT_FAILURE);
    }

    // Window

    eng::Window window("DEMO", 1000, 800);
    if (!window.init(&logger)) {
        logger.log(eng::FATAL, "Can not create window");
        exit(EXIT_FAILURE);
    }

    SDL_Delay(1000);

    window.quit();

    eng::quit();
    logger.quit();
    
    std::cout << "End program" << std::endl;

    return 0;
}