#pragma once

#include <iostream>
#include <bitset>
#include <string>
#include <ostream>
#include <fstream>

#include "Logger/LogType.hpp"

namespace eng::log {

/// @brief Pure virtual class to display the logs. All the displayer
/// are children of this class and override the Log method.
class LogDisplayer {
public:
    /// @brief Destructor
    virtual ~LogDisplayer();

    /// @brief Display a log. Pure virtual method.
    /// @param log The log which will be displayed
    virtual void Log(const LogStruct& log) = 0;

protected:
    /// @brief Create a string from a Log. Used to simplify the display.
    /// @param log The log from which the string will be created.
    /// @return The string of the log.
    virtual std::string LogToString(const LogStruct& log);

};

/// @brief Children class of LogDisplayer.
/// A displayer to display log in the terminal.
class LogDisplayerCMD : public LogDisplayer {
public:
    /// @brief Display a log
    /// @param log The log which will be displayed
    virtual void Log(const LogStruct& log) override;

protected:
    /// @brief Create a string from a Log. Used to simplify the display.
    /// @param log The log from which the string will be created.
    /// @return The string of the log.
    virtual std::string LogToString(const LogStruct& log) override;
};

/// @brief Children class of LogDisplayer.
/// A displayer to display log in a file.
class LogDisplayerTXT : public LogDisplayer {
public:
    /// @brief Constructor
    /// @param path Path of the log file
    LogDisplayerTXT(const std::string& path);

    /// @brief Destructor. Close the file.
    virtual ~LogDisplayerTXT();

    /// @brief Display a log
    /// @param log The log which will be displayed
    virtual void Log(const LogStruct& log) override;

public:
    /// @brief The log file
    std::ofstream m_file;
};

}