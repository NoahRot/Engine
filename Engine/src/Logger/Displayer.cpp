#include "Logger/Displayer.hpp"

namespace eng::log {

// Displayer - Pure Virtual class

LogDisplayer::~LogDisplayer(){}

std::string LogDisplayer::LogToString(const LogStruct& log) {
    // Create a string from the type
    std::string type_str;
    switch(log.type) {
        case Fatal:
            type_str = "FATAL";
            break;
        case Error:
            type_str = "ERROR";
            break;
        case Warning:
            type_str = "WARNING";
            break;
        case Info:
            type_str = "INFO";
            break;
        case Debug:
            type_str = "DEBUG";
            break;
        default:
            type_str = "UNKNOW";
    }
    
    // Create the string of the log
    std::string str = "[" + std::to_string((log.time%86400)/3600) + ":" + std::to_string(((log.time%86400)%3600)/60) + ":" + std::to_string(((log.time%86400)%3600)%60) + "] "
    + type_str + " [" + log.sender + "] " + log.message + "\n";

    return str;
}

// Displayer CMD

void LogDisplayerCMD::Log(const LogStruct& log) {
    std::cout << LogToString(log);
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

void LogDisplayerTXT::Log(const LogStruct& log) {
    if(m_file.is_open()) {
        m_file << LogToString(log);
    }
}

}