#include "Logger/Logger.hpp"

namespace eng::log {

Logger::Logger()
: m_whichDisplay("11111")
{
    // Reserve space to store the logs
    if (eng::_intern_::_Core::Instance().IsConfigure()) {
        Configuration config = eng::_intern_::GetConfiguration();
        m_listLog.reserve(config.log_initialLength);

        // Add the required displayer
        if (config.log_displayCMD) {
            CreateDisplayer<LogDisplayerCMD>();
        }
        if (config.log_displayTXT) {
            CreateDisplayer<LogDisplayerTXT>(config.log_displayTXTName);
        }

    }else{
        Warning("Logger", "Instance created, but the configuration is not set");
    }

    std::cout << "DEBUG : Logger created" << std::endl;
}

Logger::~Logger() {
    // Join the thread
    if (m_logThread.joinable()) {
        m_logThread.join();
    }

    // Free memory by destroying the displayer
    for(auto& displayer : m_displayer) {
        delete displayer;
    }

    std::cout << "DEBUG : Logger destroyed" << std::endl;
}

Logger& Logger::Instance() {
    static Logger s_instance;
    return s_instance;
}
    
void Logger::Fatal(const std::string& sender, const std::string& message) {
    if (m_logThread.joinable()) {
        m_logThread.join();
    }
    m_logThread = std::thread(_intern_::_LogCallback, LogLevel::Fatal, sender, message, this);
}

void Logger::Error(const std::string& sender, const std::string& message) {
    if (m_logThread.joinable()) {
        m_logThread.join();
    }
    m_logThread = std::thread(_intern_::_LogCallback, LogLevel::Error, sender, message, this);
}

void Logger::Warning(const std::string& sender, const std::string& message) {
    if (m_logThread.joinable()) {
        m_logThread.join();
    }
    m_logThread = std::thread(_intern_::_LogCallback, LogLevel::Warning, sender, message, this);
}

void Logger::Info(const std::string& sender, const std::string& message) {
    if (m_logThread.joinable()) {
        m_logThread.join();
    }
    m_logThread = std::thread(_intern_::_LogCallback, LogLevel::Info, sender, message, this);
}

void Logger::Debug(const std::string& sender, const std::string& message) {
    if (m_logThread.joinable()) {
        m_logThread.join();
    }
    m_logThread = std::thread(_intern_::_LogCallback, LogLevel::Debug, sender, message, this);
}

void Logger::SetDisplayType(LogLevel type, bool display) {
    m_whichDisplay[type] = display;
}

Logger& GetLogger() {
    return Logger::Instance();
}

namespace _intern_ {

void _LogCallback(LogLevel type, const std::string& sender, const std::string& message, Logger* logger) {
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

}