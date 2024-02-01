#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

#include "Logger/Logger.hpp"
#include "Math/Math.hpp"

namespace eng {

class Shader {
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);

    ~Shader();

    bool IsValid() const;

    void Bind() const;

    // Set Uniform

    void SetUniform1i(const std::string& varName, int var) const;
    void SetUniform1f(const std::string& varName, float var) const;

    void SetUniform2i(const std::string& varName, int v1, int v2) const;
    void SetUniform2f(const std::string& varName, float v1, float v2) const;

    void SetUniform3i(const std::string& varName, int v1, int v2, int v3) const;
    void SetUniform3f(const std::string& varName, float v1, float v2, float v3) const;

    void SetUniform4i(const std::string& varName, int v1, int v2, int v3, int v4) const;
    void SetUniform4f(const std::string& varName, float v1, float v2, float v3, float v4) const;

    void SetUniformMat3f(const std::string& varName, const math::Mat3f& mat) const;
    void SetUniformMat4f(const std::string& varName, const math::Mat4f& mat) const;

private:
    bool m_valid;

    uint32_t m_shaderProgram;

    bool LoadSource(const std::string path, std::string& source);

    bool CreateShader(GLenum type, uint32_t& shaderID, const std::string& source);

    bool CreateProgram(uint32_t vertexShader, uint32_t fragmentShader);
};

}