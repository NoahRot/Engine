#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

#include "Logger/Logger.hpp"

namespace eng {

class Shader {
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);

    ~Shader();

    bool IsValid() const;

    void Bind() const;

private:
    bool m_valid;

    uint32_t m_shaderProgram;

    bool LoadSource(const std::string path, std::string& source);

    bool CreateShader(GLenum type, uint32_t& shaderID, const std::string& source);

    bool CreateProgram(uint32_t vertexShader, uint32_t fragmentShader);
};

}