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

/// @brief A class to create logs and manage how those has to be displayed or even should be display.
class Logger {
public:
    /// @brief Constructor
    /// @param intialListLogLength The reserve place to store the logs
    Logger(uint32_t intialListLogLength = 0);

    /// @brief Destructor
    ~Logger();

    /// @brief Log a fatal error
    /// @param sender Who has sent the log
    /// @param message The content of the log
    void Fatal(const std::string& sender, const std::string& message);

    /// @brief Log an error
    /// @param sender Who has sent the log
    /// @param message The content of the log
    void Error(const std::string& sender, const std::string& message);

    /// @brief Log a warning
    /// @param sender Who has sent the log
    /// @param message The content of the log
    void Warning(const std::string& sender, const std::string& message);

    /// @brief Log an info
    /// @param sender Who has sent the log
    /// @param message The content of the log
    void Info(const std::string& sender, const std::string& message);

    /// @brief Log a debug
    /// @param sender Who has sent the log
    /// @param message The content of the log
    void Debug(const std::string& sender, const std::string& message);

    /// @brief Create a displayer to display the logs
    /// @tparam T The type of displayer
    /// @tparam ...ARG The argument for the constructor of the displayer
    /// @param ...arg The argument for the constructor of the displayer
    template<typename T, typename ...ARG>
    void CreateDisplayer(ARG ...arg);

    /// @brief Set a display type. Use to choose which type of log has to
    /// be display. 
    /// @param type The type of log
    /// @param display True : will be display, False : won't be display
    void SetDisplayType(LogType type, bool display);

private:
    friend void LogCallback(LogType type, const std::string& sender, const std::string& message, Logger* logger);

    /// @brief List of the logs
    std::vector<LogStruct> m_listLog;

    /// @brief List of the displayer on which the logs will be displayed
    std::vector<LogDisplayer*> m_displayer;

    /// @brief Use to know which type of log should be display
    std::bitset<LogType::Debug+1> m_whichDisplay;

    /// @brief Thread to display the logs
    std::thread m_logThread;
};

/// @brief Function (friend of Logger) used to log something with a thread.
/// This function is nessesary because the thread can't make a callback on
/// a method of a class. This also display the log on all displayer.
/// @param type Type of log
/// @param sender Who has sent the log
/// @param message The content of the log
/// @param logger A pointer on the Logger on which the log will be store. It
/// is also used to know if a log has to be display
void LogCallback(LogType type, const std::string& sender, const std::string& message, Logger* logger);

// Definition of the template method

template<typename T, typename ...ARG>
void Logger::CreateDisplayer(ARG ...arg) {
    T* displayer = new T(arg...);
    m_displayer.push_back(displayer);
}

}