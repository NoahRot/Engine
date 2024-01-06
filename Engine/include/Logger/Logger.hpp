#pragma once

#include <iostream>
#include <string>
#include <bitset>
#include <ctime>
#include <vector>
#include <thread>

#include "Logger/LogType.hpp"
#include "Logger/Displayer.hpp"

namespace eng::log {

class Logger {
public:
    Logger(uint32_t intialListLogLength = 0);
    ~Logger();

    void Fatal(const std::string& sender, const std::string& message);
    void Error(const std::string& sender, const std::string& message);
    void Warning(const std::string& sender, const std::string& message);
    void Info(const std::string& sender, const std::string& message);
    void Debug(const std::string& sender, const std::string& message);

    template<typename T, typename ...ARG>
    void CreateDisplayer(ARG ...arg);

    void SetDisplayType(LogType type, bool display);

private:
    friend void LogCallback(LogType type, const std::string& sender, const std::string& message, Logger* logger);

    std::vector<LogStruct> m_listLog;
    std::vector<LogDisplayer*> m_displayer;
    std::bitset<LogType::Debug+1> m_whichDisplay;
    std::thread m_logThread;
};

void LogCallback(LogType type, const std::string& sender, const std::string& message, Logger* logger);

template<typename T, typename ...ARG>
void Logger::CreateDisplayer(ARG ...arg) {
    T* displayer = new T(arg...);
    m_displayer.push_back(displayer);
}

}