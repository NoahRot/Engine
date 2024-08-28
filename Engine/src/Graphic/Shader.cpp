#include "Graphic/Shader.hpp"

namespace eng {

Shader_::Shader_(uint32_t shader_program)
: Asset(AssetType::Shader), m_shader_program(shader_program)
{}

Shader_::~Shader_() {
    glDeleteProgram(m_shader_program);
}

void Shader_::bind() {
    glUseProgram(m_shader_program);
}

void Shader_::set_uniform_1i(const std::string& varName, int var) const {
    int location = glGetUniformLocation(m_shader_program, varName.c_str());
    glUniform1i(location, var);
}

void Shader_::set_uniform_1f(const std::string& varName, float var) const {
    int location = glGetUniformLocation(m_shader_program, varName.c_str());
    glUniform1f(location, var);
}

void Shader_::set_uniform_2i(const std::string& varName, int v1, int v2) const {
    int location = glGetUniformLocation(m_shader_program, varName.c_str());
    glUniform2i(location, v1, v2);
}

void Shader_::set_uniform_2f(const std::string& varName, float v1, float v2) const {
    int location = glGetUniformLocation(m_shader_program, varName.c_str());
    glUniform2f(location, v1, v2);
}

void Shader_::set_uniform_3i(const std::string& varName, int v1, int v2, int v3) const {
    int location = glGetUniformLocation(m_shader_program, varName.c_str());
    glUniform3i(location, v1, v2, v3);
}
void Shader_::set_uniform_3f(const std::string& varName, float v1, float v2, float v3) const {
    int location = glGetUniformLocation(m_shader_program, varName.c_str());
    glUniform3f(location, v1, v2, v3);
}

void Shader_::set_uniform_4i(const std::string& varName, int v1, int v2, int v3, int v4) const {
    int location = glGetUniformLocation(m_shader_program, varName.c_str());
    glUniform4i(location, v1, v2, v3, v4);
}
void Shader_::set_uniform_4f(const std::string& varName, float v1, float v2, float v3, float v4) const {
    int location = glGetUniformLocation(m_shader_program, varName.c_str());
    glUniform4f(location, v1, v2, v3, v4);
}

void Shader_::set_uniform_mat3f(const std::string& varName, const math::Mat3f& mat) const {
    int location = glGetUniformLocation(m_shader_program, varName.c_str());
    glUniformMatrix3fv(location, 1, false, mat.front_ptr());
}

void Shader_::set_uniform_mat4f(const std::string& varName, const math::Mat4f& mat) const {
    int location = glGetUniformLocation(m_shader_program, varName.c_str());
    glUniformMatrix4fv(location, 1, false, mat.front_ptr());
}

void Shader_::set_uniform_mat3f(const std::string& varName, const mat::Mat3f& mat) const {
    int location = glGetUniformLocation(m_shader_program, varName.c_str());
    glUniformMatrix3fv(location, 1, false, &mat(0,0));
}

void Shader_::set_uniform_mat4f(const std::string& varName, const mat::Mat4f& mat) const {
    int location = glGetUniformLocation(m_shader_program, varName.c_str());
    glUniformMatrix4fv(location, 1, false, &mat(0,0));
}



namespace _intern_ {

bool shader_load_source(const std::string path, std::string& source) {
    // Open file
    std::fstream shaderFile;
    shaderFile.open(path);
    if (shaderFile.fail()) {
        eng::get_logger().error("Shader", "Can't open shader source file. File name : " + path);
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

bool shader_create_shader(GLenum type, uint32_t& shader_index, const std::string& source) {
    // Define error variable
    int success;
    char infoLog[512];

    // Compile the shader
    shader_index = glCreateShader(type);
    const char* sourceChar = source.c_str();
    glShaderSource(shader_index, 1, &sourceChar, nullptr);
    glCompileShader(shader_index);

    // Check for errors
    glGetShaderiv(shader_index, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader_index, 512, NULL, infoLog);
        get_logger().error("Shader", "Error during shader compilation. Error message : " + std::string(infoLog));

        return false;
    }

    return true;
}

bool shader_create_program(uint32_t vertex_shader, uint32_t fragment_shader, uint32_t& shader_program) {
    // Define error variable
    int success;
    char infoLog[512];

    // Create shader program
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    
    // Check for errors
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
        get_logger().error("Shader", "Error during program compilation. Error message : " + std::string(infoLog));
        return false;
    }

    return true;
}

}

}

