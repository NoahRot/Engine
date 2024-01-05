#pragma once

#include <iostream>
#include <ostream>
#include <string>

namespace eng {

class Logger {
public:

private:
    std::string m_path;
    std::ofstream m_file;
};

}