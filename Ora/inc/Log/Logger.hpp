#pragma once

#include <inttypes.h>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>

namespace ora {

/// @brief Level of log and display modes
enum LogLevel {
    // Levels
    Fatal   = 0b00000001,
    Error   = 0b00000010,
    Warning = 0b00000100,
    Info    = 0b00001000,
    Debug   = 0b00010000,

    //Display modes
    DispCMD = 0b00100000,
    DispTXT = 0b01000000
};

/// @brief State of the log class
typedef uint8_t LogState;

/// @brief Callback function for log. Can be use for multithreading.
/// @param level Level of log
/// @param message Message of log
/// @param cmd Are we log in CMD
/// @param txt Are we log in texte log file
/// @param stream Log file
void _log_callback(LogLevel level, const std::string& message, bool cmd, bool txt, std::ofstream& stream);

/// @brief Logger class
class Logger {
public:
    /// @brief Constructor
    /// @param log_file_path Path to the log file 
    Logger(const std::string& log_file_path);

    /// @brief Constructor
    /// @param state State of the log class
    /// @param log_file_path Path to the log file
    Logger(LogState state, const std::string& log_file_path);

    /// @brief Destructor
    ~Logger();

    /// @brief Set display in CMD
    /// @param state True for display in CMD
    void set_display_cmd(bool state);

    /// @brief Set display in log file
    /// @param state True for display in log file
    void set_display_txt(bool state);

    /// @brief Set display level of log
    /// @param level The level of log to set
    /// @param state True for display, false otherwise
    void set_level(LogLevel level, bool state);

    /// @brief Is the given level/display mode enable
    /// @param level Level of log or display mode
    /// @return True if enable, false otherwise
    bool is_display(LogLevel level);

    /// @brief Get the state of the log class
    /// @return The state of the log class
    LogState get_state() const;

    /// @brief Log a message
    /// @param level Level of the log
    /// @param message Message of the log
    void log(LogLevel level, const std::string& message);

private:
    /// @brief Current state of the log class
    LogState m_state;

    /// @brief Log file
    std::ofstream m_log_file;
};

}