#include "Logger/Logger.hpp"

namespace eng::log {

Logger::Logger(uint32_t intialListLogLength)
: m_whichDisplay("11111")
{
    m_listLog.reserve(intialListLogLength);
}

Logger::~Logger() {
    if (m_logThread.joinable()) {
        m_logThread.join();
    }

    for(auto& displayer : m_displayer) {
        delete displayer;
    }
}
    
void Logger::Fatal(const std::string& sender, const std::string& message) {
    if (m_logThread.joinable()) {
        m_logThread.join();
    }
    m_logThread = std::thread(LogCallback, LogType::Fatal, sender, message, this);
}

void Logger::Error(const std::string& sender, const std::string& message) {
    if (m_logThread.joinable()) {
        m_logThread.join();
    }
    m_logThread = std::thread(LogCallback, LogType::Error, sender, message, this);
}

void Logger::Warning(const std::string& sender, const std::string& message) {
    if (m_logThread.joinable()) {
        m_logThread.join();
    }
    m_logThread = std::thread(LogCallback, LogType::Warning, sender, message, this);
}

void Logger::Info(const std::string& sender, const std::string& message) {
    if (m_logThread.joinable()) {
        m_logThread.join();
    }
    m_logThread = std::thread(LogCallback, LogType::Info, sender, message, this);
}

void Logger::Debug(const std::string& sender, const std::string& message) {
    if (m_logThread.joinable()) {
        m_logThread.join();
    }
    m_logThread = std::thread(LogCallback, LogType::Debug, sender, message, this);
}

void Logger::SetDisplayType(LogType type, bool display) {
    m_whichDisplay[type] = display;
}

void LogCallback(LogType type, const std::string& sender, const std::string& message, Logger* logger) {
    // Add the new log
    logger->m_listLog.push_back(LogStruct{time(0), type, sender, message});

    // Log in each displayer
    for(auto& display : logger->m_displayer) {
        if (logger->m_whichDisplay[type]) {
            display->Log(logger->m_listLog.back());
        }
    }
}

}