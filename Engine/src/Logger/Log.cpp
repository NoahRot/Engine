#include "Logger/Log.hpp"

namespace eng {

/*  ==========================
    === Callback functions ===
    ==========================  */

std::string _log_time_to_str(time_t time) {
    return std::string("[" + (((time%86400)/3600 < 10)? (std::string)"0" : (std::string)"") + std::to_string((time%86400)/3600)         // Hours
        + ":" + ((((time%86400)%3600)/60 < 10)? (std::string)"0" : (std::string)"") + std::to_string(((time%86400)%3600)/60)            // Minutes
        + ":" + ((((time%86400)%3600)%60 < 10)? (std::string)"0" : (std::string)"") + std::to_string(((time%86400)%3600)%60) + "] ");   // Seconds
}

std::string _log_level_to_str(LogType level, bool with_color) {
    switch(level) {
        case LogType::FATAL:
            if (with_color) {return "\x1b[1m\x1b[91mFATAL     \033[0m";}
            else {return "FATAL     ";}
            break;
        case LogType::ERROR:
            if (with_color) {return "\x1b[1m\x1b[33mERROR     \033[0m";}
            else {return "ERROR     ";}
            break;
        case LogType::WARNING:
            if (with_color) {return "\x1b[1m\x1b[35mWARNING   \033[0m";}
            else {return "WARNING   ";}
            break;
        case LogType::INFO:
            if (with_color) {return "\x1b[1m\x1b[32mINFO      \033[0m";}
            else {return "INFO      ";}
            break;
        case LogType::DEBUG:
            if (with_color) {return "\x1b[1m\x1b[34mDEBUG     \033[0m";}
            else {return "DEBUG     ";}
            break;
        case LogType::TRACE:
            if (with_color) {return "\x1b[1m\x1b[36mTRACE     \033[0m";}
            else {return "TRACE     ";}
            break;
        default:
            if (with_color) {return "\x1b[1m\x1b[37mUNKNOW    \033[0m";}
            else {return "UNKNOW    ";}
    }
}

void _log_callback(bool cmd, bool txt, time_t time, LogType level, const std::string& message, std::ofstream* stream) {
    if (cmd) {
        std::cout << "\x1b[90m" << _log_time_to_str(time) << _log_level_to_str(level, true) << message << "\n";
    }
    if(txt && stream && stream->is_open()) {
        *stream << _log_time_to_str(time) << _log_level_to_str(level, false) << message << "\n";
    }
}

/*  ====================
    === Logger class ===
    ====================  */

Logger::Logger()
:m_filter(0b00111111)
{
    m_is_init = false;
}

Logger::~Logger() {}

bool Logger::init(bool disp_cmd, bool disp_txt, const std::string& txt_name) {
    // Can't be initialize twice
    if (m_is_init) {
        return false;
    }

    // Set the filter for terminal and text file
    m_filter = (m_filter & ~(CMD)) | (CMD*disp_cmd);
    m_filter = (m_filter & ~(TXT)) | (TXT*disp_txt);

    // Open the text file if necessary
    if (disp_txt) {
        m_file.open(txt_name + ".log");
        if (!m_file.is_open()) {
            return false;
        }
    }

    // Initialize complete
    m_is_init = true;
    return true;
}

void Logger::quit() {
    // Join the thread
    if (m_thread.joinable()) {
        m_thread.join();
    }

    // Close the file
    if (m_file.is_open()) {
        m_file.close();
    } 
}

void Logger::set_level(LogType level, bool display) {
    if (level <= TRACE) {
        m_filter = (m_filter & ~(level)) | (level*display);
    }
}

void Logger::log(LogType level, const std::string& message) {
    // Join the thread
    if (m_thread.joinable()) {
        m_thread.join();
    }

    // Log on a separate thread
    if ((level & m_filter) == level) {
        m_thread = std::thread(_log_callback, (CMD & m_filter) == CMD, (TXT & m_filter) == TXT, time(NULL), level, message, &m_file);
    }
}

}