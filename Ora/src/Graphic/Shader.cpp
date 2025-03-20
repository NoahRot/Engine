#include "Graphic/Shader.hpp"

namespace ora {

Shader::Shader(int32_t index)
: m_index(index)
{
    // Find all uniform variables
    int uniform_count = 0;

    // Query the number of active uniforms in the shader program
    glGetProgramiv(m_index, GL_ACTIVE_UNIFORMS, &uniform_count);

    char uniform_name[256];
    for (int i = 0; i < uniform_count; i++) {
        GLint size;
        GLenum type;

        // Get uniform info
        glGetActiveUniform(m_index, i, sizeof(uniform_name), nullptr, &size, &type, uniform_name);

        // Get uniform location
        int location = glGetUniformLocation(m_index, uniform_name);
        if (location != -1) {  // If uniform exists in the program
            m_uniform_map[uniform_name] = location;
        }
    }
}

Shader::~Shader() {
    glDeleteProgram(m_index);
}

void Shader::use_shader() const {
    glUseProgram(m_index);
}

const std::unordered_map<std::string, int>& Shader::get_uniform_map() const {
    return m_uniform_map;
}

bool Shader::uniform_validity(const std::string& var_name) const {
    return m_uniform_map.find(var_name) != m_uniform_map.end();
}

void Shader::set_1i(const std::string& var_name, int var) {
    glUniform1i(m_uniform_map[var_name], var);
}

void Shader::set_1f(const std::string& var_name, float var) {
    glUniform1f(m_uniform_map[var_name], var);
}

void Shader::set_1d(const std::string& var_name, double var) {
    glUniform1d(m_uniform_map[var_name], var);
}

void Shader::set_2i(const std::string& var_name, const mat::Vec2i& var) {
    glUniform2i(m_uniform_map[var_name], var[0], var[1]);
}

void Shader::set_2f(const std::string& var_name, const mat::Vec2f& var) {
    glUniform2f(m_uniform_map[var_name], var[0], var[1]);
}

void Shader::set_2d(const std::string& var_name, const mat::Vec2d& var) {
    glUniform2d(m_uniform_map[var_name], var[0], var[1]);
}

void Shader::set_3i(const std::string& var_name, const mat::Vec3i& var) {
    glUniform3i(m_uniform_map[var_name], var[0], var[1], var[2]);
}

void Shader::set_3f(const std::string& var_name, const mat::Vec3f& var) {
    glUniform3f(m_uniform_map[var_name], var[0], var[1], var[2]);
}

void Shader::set_3d(const std::string& var_name, const mat::Vec3d& var) {
    glUniform3d(m_uniform_map[var_name], var[0], var[1], var[2]);
}

void Shader::set_4i(const std::string& var_name, const mat::Vec4i& var) {
    glUniform4i(m_uniform_map[var_name], var[0], var[1], var[2], var[3]);
}

void Shader::set_4f(const std::string& var_name, const mat::Vec4f& var) {
    glUniform4f(m_uniform_map[var_name], var[0], var[1], var[2], var[3]);
}

void Shader::set_4d(const std::string& var_name, const mat::Vec4d& var) {
    glUniform4d(m_uniform_map[var_name], var[0], var[1], var[2], var[3]);
}

void Shader::set_mat3f(const std::string& var_name, const mat::Mat3f& var) {
    glUniformMatrix3fv(m_uniform_map[var_name], 1, false, &var(0,0));
}

void Shader::set_mat3d(const std::string& var_name, const mat::Mat3d& var) {
    glUniformMatrix3dv(m_uniform_map[var_name], 1, false, &var(0,0));
}

void Shader::set_mat4f(const std::string& var_name, const mat::Mat4f& var) {
    glUniformMatrix4fv(m_uniform_map[var_name], 1, false, &var(0,0));
}

void Shader::set_mat4d(const std::string& var_name, const mat::Mat4d& var) {
    glUniformMatrix4dv(m_uniform_map[var_name], 1, false, &var(0,0));
}




ShaderManager::ShaderManager() {
    Logger::instance().log(Info, "Shader manager created");
}

ShaderManager::~ShaderManager() {
    Logger::instance().log(Info, "Shader manager destroyed");
}

int32_t ShaderManager::load_shader(const std::string& vertex_path, const std::string& fragment_path) {
    // Load shaders source code
    std::string vertex_source_code;
    std::string fragment_source_code;

    if (!load_source(fragment_path, fragment_source_code)) {
        return -1;
    }
    if (!load_source(vertex_path, vertex_source_code)) {
        return -1;
    }

    // Create shaders
    uint32_t vertex_shader;
    uint32_t fragment_shader;

    if (!create_shader(GL_VERTEX_SHADER, vertex_shader, vertex_source_code)) {
        glDeleteShader(vertex_shader);
        return -1;
    }

    if (!create_shader(GL_FRAGMENT_SHADER, fragment_shader, fragment_source_code)) {
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        return -1;
    }

    // Create shader program
    uint32_t shader_program;
    if (!create_program(vertex_shader, fragment_shader, shader_program)) {
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        return -1;
    }

    // Delete shaders
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    // Create and put the shader in the vector
    int32_t index = m_shaders.add(shader_program);

    return index;
}

bool ShaderManager::free_shader(int32_t index) {
    return m_shaders.remove(index);
}

Shader* ShaderManager::get_shader(int32_t index) {
    return &m_shaders.get(index);
}

bool ShaderManager::valid_shader(int32_t index) {
    return m_shaders.validity(index);
}

bool ShaderManager::load_source(const std::string path, std::string& source) {
    // Open file
    std::fstream shader_file;
    shader_file.open(path);
    if (shader_file.fail()) {
        Logger::instance().log(Info, "Can not load shader source. Shader path : " + path);
        return false;
    }

    // Load the source file
    std::stringstream stream;
    stream << shader_file.rdbuf();
    source = stream.str();

    // Close file
    shader_file.close();

    return true;
}

bool ShaderManager::create_shader(GLenum type, uint32_t& shader_index, const std::string& source) {
    // Define error variable
    int success;
    char info_log[512];

    // Compile the shader
    shader_index = glCreateShader(type);
    const char* sourceChar = source.c_str();
    glShaderSource(shader_index, 1, &sourceChar, nullptr);
    glCompileShader(shader_index);

    // Check for errors
    glGetShaderiv(shader_index, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader_index, 512, NULL, info_log);
        std::string shader_type_str;
        switch (type) {
            case GL_VERTEX_SHADER:
                shader_type_str = "vertex";
                break;
            case GL_FRAGMENT_SHADER:
                shader_type_str = "fragment";
                break;
            default:
                break;
        }
        Logger::instance().log(Info, "Can not compile " + shader_type_str + " shader. Error :\n" + std::string(info_log));
        return false;
    }

    return true;
}   

bool ShaderManager::create_program(uint32_t vertex_shader, uint32_t fragment_shader, uint32_t& shader_program) {
    // Define error variable
    int success;
    char info_log[512];

    // Create shader program
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    
    // Check for errors
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_program, 512, NULL, info_log);
        Logger::instance().log(Info, "Can not bind shader to shader program. Error :\n" + std::string(info_log));
        return false;
    }

    return true;
}

}