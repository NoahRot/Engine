#pragma once

#include <string>

namespace eng::log {

/// @brief All the type of log
enum LogLevel {
    Fatal   = 0,
    Error   = 1,
    Warning = 2,
    Info    = 3,
    Debug   = 4
};

/// @brief Structure of a log
struct LogStruct {
    time_t      time;
    LogLevel    level;
    std::string sender;
    std::string message;
};

}