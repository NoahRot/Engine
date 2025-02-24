#include "Logger/Logger.hpp"

namespace eng::log {

Logger::Logger()
: m_whichDisplay("11111")
{
    // Reserve space to store the logs
    if (eng::_intern_::_Core::instance().is_configure()) {
        Configuration config = eng::get_configuration();
        m_listLog.reserve(config.log_initialLength);

        // Add the required displayer
        if (config.log_displayCMD) {
            create_displayer<LogDisplayerCMD>();
        }
        if (config.log_displayTXT) {
            create_displayer<LogDisplayerTXT>(config.log_displayTXTName);
        }

    }else{
        warning("Logger", "Instance created, but the configuration is not set");
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

Logger& Logger::instance() {
    static Logger s_instance;
    return s_instance;
}
    
void Logger::fatal(const std::string& sender, const std::string& message) {
    if (m_logThread.joinable()) {
        m_logThread.join();
    }
    m_logThread = std::thread(_intern_::_LogCallback, LogLevel::Fatal, sender, message, this);
}

void Logger::error(const std::string& sender, const std::string& message) {
    if (m_logThread.joinable()) {
        m_logThread.join();
    }
    m_logThread = std::thread(_intern_::_LogCallback, LogLevel::Error, sender, message, this);
}

void Logger::warning(const std::string& sender, const std::string& message) {
    if (m_logThread.joinable()) {
        m_logThread.join();
    }
    m_logThread = std::thread(_intern_::_LogCallback, LogLevel::Warning, sender, message, this);
}

void Logger::info(const std::string& sender, const std::string& message) {
    if (m_logThread.joinable()) {
        m_logThread.join();
    }
    m_logThread = std::thread(_intern_::_LogCallback, LogLevel::Info, sender, message, this);
}

void Logger::debug(const std::string& sender, const std::string& message) {
    if (m_logThread.joinable()) {
        m_logThread.join();
    }
    m_logThread = std::thread(_intern_::_LogCallback, LogLevel::Debug, sender, message, this);
}

void Logger::set_display_type(LogLevel level, bool display) {
    m_whichDisplay[level] = display;
}

namespace _intern_ {

void _LogCallback(LogLevel level, const std::string& sender, const std::string& message, Logger* logger) {
    // Add the new log
    logger->m_listLog.push_back(LogStruct{time(0), level, sender, message});

    // Log in each displayer
    if (logger->m_whichDisplay[level]) {
        for(auto& display : logger->m_displayer) {
                display->log(logger->m_listLog.back());
        }
    }
}

}

}