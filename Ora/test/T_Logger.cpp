#include "Log/Logger.hpp"
#include "Engine/Configuration.hpp"
#include "Engine/Engine.hpp"

int main(int argc, char* argv[]) {

    ora::Configuration config;
    config.log_file_name = "test/log/Log_test.log";

    ora::_init_logger(config.log_state, config.log_file_name);
    ora::Logger& logger = ora::Logger::instance();

    if (logger.is_display(ora::LogLevel::Debug)) {
        std::cout << "Show debug" << std::endl;
    }

    logger.set_level(ora::LogLevel::Debug, false);

    if (!logger.is_display(ora::LogLevel::Debug)) {
        std::cout << "Not show debug" << std::endl;
    }

    logger.log(ora::Fatal, "Fatal test");
    logger.log(ora::Error, "Error test");
    logger.log(ora::Warning, "Warning test");
    logger.log(ora::Info, "Info test");
    logger.log(ora::Debug, "Debug test");
    
    return 0;
}