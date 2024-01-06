#pragma once

#include <iostream>
#include <bitset>
#include <string>
#include <ostream>
#include <fstream>

#include "Logger/LogType.hpp"

namespace eng::log {

class LogDisplayer {
public:
    virtual ~LogDisplayer();

    virtual void Log(const LogStruct& log) = 0;

protected:
    std::string LogToString(const LogStruct& log);

};

class LogDisplayerCMD : public LogDisplayer {
public:
    virtual void Log(const LogStruct& log) override;
};

class LogDisplayerTXT : public LogDisplayer {
public:
    LogDisplayerTXT(const std::string& path);

    virtual ~LogDisplayerTXT();

    virtual void Log(const LogStruct& log) override;

public:
    std::ofstream m_file;
};

}