#include "Logger/Displayer.hpp"

namespace eng::log {

// Displayer - Pure Virtual class

LogDisplayer::~LogDisplayer(){}

std::string LogDisplayer::log_to_string(const LogStruct& log) {
    // Create a string from the type
    std::string type_str;
    switch(log.level) {
        case Fatal:
            type_str = "FATAL     ";
            break;
        case Error:
            type_str = "ERROR     ";
            break;
        case Warning:
            type_str = "WARNING   ";
            break;
        case Info:
            type_str = "INFO      ";
            break;
        case Debug:
            type_str = "DEBUG     ";
            break;
        default:
            type_str = "UNKNOW    ";
    }
    
    // Create the string of the log
    // Create time
    std::string str = "[" + (((log.time%86400)/3600 < 10)? (std::string)"0" : (std::string)"") + std::to_string((log.time%86400)/3600)
         + ":" + ((((log.time%86400)%3600)/60 < 10)? (std::string)"0" : (std::string)"") + std::to_string(((log.time%86400)%3600)/60)
         + ":" + ((((log.time%86400)%3600)%60 < 10)? (std::string)"0" : (std::string)"") + std::to_string(((log.time%86400)%3600)%60) + "] "
    // Add the type of log
         + type_str
    // Add the sender
         + " [" + log.sender + "] "
    // Add message
         + log.message + "\n";

    return str;
}

// Displayer CMD

void LogDisplayerCMD::log(const LogStruct& log) {
    std::cout << log_to_string(log);
}

std::string LogDisplayerCMD::log_to_string(const LogStruct& log) {
    // Create a string from the type
    std::string type_str;
    std::string color;
    switch(log.level) {
        case Fatal:
            type_str = "FATAL     ";
            color = "\x1b[91m"; // Bright red
            break;
        case Error:
            type_str = "ERROR     ";
            color = "\x1b[31m"; // Red
            break;
        case Warning:
            type_str = "WARNING   ";
            color = "\x1b[33m"; // Yellow
            break;
        case Info:
            type_str = "INFO      ";
            color = "\x1b[32m"; // Green
            break;
        case Debug:
            type_str = "DEBUG     ";
            color = "\x1b[34m"; // Blue
            break;
        default:
            type_str = "UNKNOW    ";
            color = "\x1b[37m"; // White
    }
    
    // Create the string of the log
    // Create time
    std::string str = "[" + (((log.time%86400)/3600 < 10)? (std::string)"0" : (std::string)"") + std::to_string((log.time%86400)/3600)
         + ":" + ((((log.time%86400)%3600)/60 < 10)? (std::string)"0" : (std::string)"") + std::to_string(((log.time%86400)%3600)/60)
         + ":" + ((((log.time%86400)%3600)%60 < 10)? (std::string)"0" : (std::string)"") + std::to_string(((log.time%86400)%3600)%60) + "] "
    // Add the type of log
         + color + type_str + "\033[0m"
    // Add the sender
         + " [" + log.sender + "] "
    // Add message
         + log.message + "\n";

    return str;
}

// Displayer TXT

LogDisplayerTXT::LogDisplayerTXT(const std::string& path)
: m_file(path)
{
    // Check if the file has been opend
    if(!m_file.is_open()) {
        std::cerr << "DISPLAYER TXT ERROR : CAN NOT OPEN FILE" << std::endl;
    }
}
    
LogDisplayerTXT::~LogDisplayerTXT() {
    if(m_file.is_open()) {
        m_file.close();
    }
}

void LogDisplayerTXT::log(const LogStruct& log) {
    if(m_file.is_open()) {
        m_file << log_to_string(log);
    }
}

}