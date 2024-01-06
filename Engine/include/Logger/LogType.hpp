#pragma once

#include <string>

namespace eng::log {

enum LogType {
    Fatal   = 0,
    Error   = 1,
    Warning = 2,
    Info    = 3,
    Debug   = 4
};

struct LogStruct {
    time_t      time;
    LogType     type;
    std::string sender;
    std::string message;
};

}