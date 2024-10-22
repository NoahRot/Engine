#include "Log/Logger.hpp"

namespace ora {

void _log_callback(LogLevel level, const std::string& message, bool cmd, bool txt, std::ofstream& stream) {
    // Create log string and take the time of the log
    std::string log_lvl;
    std::string color_lvl;
    time_t log_time = time(0);

    // Add the level of the log and color
    switch (level)
    {
    case Fatal:
        log_lvl = "FATAL";
        color_lvl = "\033[91m";
        break;
    case Error:
        log_lvl = "ERROR";
        color_lvl = "\033[93m";
        break;
    case Warning:
        log_lvl = "WARNING";
        color_lvl = "\033[95m";
        break;
    case Info:
        log_lvl = "INFO";
        color_lvl = "\033[94m";
        break;
    case Debug:
        log_lvl = "DEBUG";
        color_lvl = "\033[92m";
        break;
    default:
        log_lvl = "UNKNOWN";
        color_lvl = "\033[97m";
        break;
    }

    // Time to string
    std::string time_str = "[" + (((log_time%86400)/3600 < 10)? (std::string)"0" : (std::string)"") + std::to_string((log_time%86400)/3600)
         + ":" + ((((log_time%86400)%3600)/60 < 10)? (std::string)"0" : (std::string)"") + std::to_string(((log_time%86400)%3600)/60)
         + ":" + ((((log_time%86400)%3600)%60 < 10)? (std::string)"0" : (std::string)"") + std::to_string(((log_time%86400)%3600)%60) + "] ";
    
    // CMD Display
    if (cmd) {
        std::cout << "\033[90m" << time_str << color_lvl << log_lvl << "\033[37m : " << message << "\033[0m" << std::endl;
    }
    
    // Txt Display
    if (txt) {
        stream << time_str << " " << log_lvl << " : " << message << "\n";
    }
}

Logger::Logger(const std::string& log_file_path)
: m_state(0b11111111)
{
    m_log_file.open(log_file_path);

    if (!m_log_file.is_open()) {
        set_display_txt(false);

        log(Error, "Logger can not open log file. Log file path : " + log_file_path);
    }

    log(ora::Info, "Logger created");
}

Logger::Logger(LogState state, const std::string& log_file_path)
: m_state(state)
{
    m_log_file.open(log_file_path);

    if (!m_log_file.is_open()) {
        set_display_txt(false);

        log(Error, "Logger can not open log file. Log file path : " + log_file_path);
    }

    log(ora::Info, "Logger created");
}

Logger::~Logger() {
    m_log_file.close();

    log(ora::Info, "Logger destroyed");
}

void Logger::set_display_cmd(bool state) {
    m_state = (m_state & ~(DispCMD)) | (DispCMD*state);
}

void Logger::set_display_txt(bool state) {
    if (state && !m_log_file.is_open()){
        log(Error, "Logger file has not been open, thus can not write in it.");
        return;
    }
    m_state = (m_state & ~(DispTXT)) | (DispTXT*state);
}

void Logger::set_level(LogLevel level, bool state) {
    if (state && (level & DispTXT) == DispTXT && !m_log_file.is_open()){
        log(Error, "Logger file has not been open, thus can not write in it.");
        return;
    }
    m_state = (m_state & ~(level)) | (level*state);
}

bool Logger::is_display(LogLevel level) {
    return (m_state & level) == level;
}

LogState Logger::get_state() const {
    return m_state;
}

void Logger::log(LogLevel level, const std::string& message) {
    if ((m_state &  level) == level){
        _log_callback(level, message, (m_state & DispCMD) == DispCMD, (m_state & DispTXT) == DispTXT, m_log_file);
    }
}

}