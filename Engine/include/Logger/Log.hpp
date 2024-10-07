#pragma once

#include <iostream>
#include <ostream>
#include <fstream>
#include <string>
#include <thread>
#include <array>

namespace eng {

/*  ===================================
    === Type definition for the log ===
    ===================================  */

// Type for log, level and display methods
enum LogType {
    // Levels of log
    FATAL       = 0b00000001,
    ERROR       = 0b00000010,
    WARNING     = 0b00000100,
    INFO        = 0b00001000,
    DEBUG       = 0b00010000,
    TRACE       = 0b00100000,

    // Type of log, CMD for terminal, TXT for a text file
    CMD         = 0b01000000,
    TXT         = 0b10000000
};

// Filter for log
typedef uint8_t LogFilter;

/*  ==========================
    === Callback functions ===
    ==========================  */

/// @brief Function to create a string from a given time 
/// @param time The time
/// @return A string representing the time
std::string _log_time_to_str(time_t time);

/// @brief Function to create a string from a level
/// @param level The level
/// @param with_color If the level should be use with colors (for CMD) or not (for text file)
/// @return A string representing the level
std::string _log_level_to_str(LogType level, bool with_color);

/// @brief Callback function to use with multithreading for log
/// @param cmd If the log is display on the terminal
/// @param txt If the log is display on the text file
/// @param time The time of the log
/// @param level The level of the log
/// @param message The message of the log
/// @param stream The stream of the text file
void _log_callback(bool cmd, bool txt, time_t time, LogType level, const std::string& message, std::ofstream* stream);

/*  ====================
    === Logger class ===
    ====================  */

// Class to create and display log
class Logger {
public:
    /// @brief Constructor
    Logger();

    /// @brief Destructor
    ~Logger();

    /// @brief Initialize the class
    /// @param disp_cmd Should be display of CMD
    /// @param disp_txt Should be display in a text file
    /// @param txt_name The name of the text file
    /// @return True if the initialization has succeed
    bool init(bool disp_cmd, bool disp_txt, const std::string& txt_name = "");

    /// @brief Quit the class
    void quit();

    /// @brief Set if a level should be display or not
    /// @param level Level to display or not
    /// @param display If the level should be display
    void set_level(LogType level, bool display);

    /// @brief Log function
    /// @param level The level of log
    /// @param message The message of log
    void log(LogType level, const std::string& message);

private:
    bool m_is_init;         // Is the class initialize 
    std::thread m_thread;   // Thread for the log function
    LogFilter m_filter;     // Filter of the log class
    std::ofstream m_file;   // The stream of the file
};

}