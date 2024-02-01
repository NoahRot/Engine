#include "Graphic/Shader.hpp"

namespace eng {

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
: m_valid(true)
{
    // Load shaders source code
    std::string vertexSourceCode;
    std::string fragmentSourceCode;
    if (!LoadSource(fragmentPath, fragmentSourceCode)) {
        m_valid = false;
        return;
    }
    if (!LoadSource(vertexPath, vertexSourceCode)) {
        m_valid = false;
        return;
    }
    
    // Create shaders
    uint32_t vertexShader;
    uint32_t fragmentShader;
    if (!CreateShader(GL_VERTEX_SHADER, vertexShader, vertexSourceCode)) {
        glDeleteShader(vertexShader);
        m_valid = false;
        return;
    }
    if (!CreateShader(GL_FRAGMENT_SHADER, fragmentShader, fragmentSourceCode)) {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        m_valid = false;
        return;
    }

    // Create shader program
    if (!CreateProgram(vertexShader, fragmentShader)) {
        m_valid = false;
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return;
    } 

    // Delete shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader() {
    glDeleteProgram(m_shaderProgram);
}

bool Shader::LoadSource(const std::string path, std::string& source) {
    // Open file
    std::fstream shaderFile;
    shaderFile.open(path);
    if (shaderFile.fail()) {
        eng::GetLogger().Error("Shader", "Can't open shader source file. File name : " + path);
        return false;
    }

    // Load the source file
    std::stringstream stream;
    stream << shaderFile.rdbuf();
    source = stream.str();

    // Close file
    shaderFile.close();

    return true;
}

bool Shader::IsValid() const {
    return m_valid;
}

void Shader::Bind() const {
    glUseProgram(m_shaderProgram);
}

// Set Uniform

void Shader::SetUniform1i(const std::string& varName, int var) const {
    int location = glGetUniformLocation(m_shaderProgram, varName.c_str());
    glUniform1i(location, var);
}

void Shader::SetUniform1f(const std::string& varName, float var) const {
    int location = glGetUniformLocation(m_shaderProgram, varName.c_str());
    glUniform1f(location, var);
}

void Shader::SetUniform2i(const std::string& varName, int v1, int v2) const {
    int location = glGetUniformLocation(m_shaderProgram, varName.c_str());
    glUniform2i(location, v1, v2);
}

void Shader::SetUniform2f(const std::string& varName, float v1, float v2) const {
    int location = glGetUniformLocation(m_shaderProgram, varName.c_str());
    glUniform2f(location, v1, v2);
}

void Shader::SetUniform3i(const std::string& varName, int v1, int v2, int v3) const {
    int location = glGetUniformLocation(m_shaderProgram, varName.c_str());
    glUniform3i(location, v1, v2, v3);
}
void Shader::SetUniform3f(const std::string& varName, float v1, float v2, float v3) const {
    int location = glGetUniformLocation(m_shaderProgram, varName.c_str());
    glUniform3f(location, v1, v2, v3);
}

void Shader::SetUniform4i(const std::string& varName, int v1, int v2, int v3, int v4) const {
    int location = glGetUniformLocation(m_shaderProgram, varName.c_str());
    glUniform4i(location, v1, v2, v3, v4);
}
void Shader::SetUniform4f(const std::string& varName, float v1, float v2, float v3, float v4) const {
    int location = glGetUniformLocation(m_shaderProgram, varName.c_str());
    glUniform4f(location, v1, v2, v3, v4);
}

void Shader::SetUniformMat3f(const std::string& varName, const math::Mat3f& mat) const {
    int location = glGetUniformLocation(m_shaderProgram, varName.c_str());
    glUniformMatrix3fv(location, 1, false, mat.FrontPtr());
}

void Shader::SetUniformMat4f(const std::string& varName, const math::Mat4f& mat) const {
    int location = glGetUniformLocation(m_shaderProgram, varName.c_str());
    glUniformMatrix4fv(location, 1, false, mat.FrontPtr());
}

bool Shader::CreateShader(GLenum type, uint32_t& shaderID, const std::string& source) {
    // Define error variable
    int success;
    char infoLog[512];

    // Compile the shader
    shaderID = glCreateShader(type);
    const char* sourceChar = source.c_str();
    glShaderSource(shaderID, 1, &sourceChar, nullptr);
    glCompileShader(shaderID);

    // Check for errors
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
        GetLogger().Error("Shader", "Error during shader compilation. Error message : " + std::string(infoLog));

        return false;
    }

    return true;
}

bool Shader::CreateProgram(uint32_t vertexShader, uint32_t fragmentShader) {
    // Define error variable
    int success;
    char infoLog[512];

    // Create shader program
    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, vertexShader);
    glAttachShader(m_shaderProgram, fragmentShader);
    glLinkProgram(m_shaderProgram);
    
    // Check for errors
    glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_shaderProgram, 512, NULL, infoLog);
        GetLogger().Error("Shader", "Error during program compilation. Error message : " + std::string(infoLog));
        return false;
    }

    return true;
}

}