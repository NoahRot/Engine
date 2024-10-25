#include "Graphic/Shader.hpp"

namespace ora {

ShaderManager::ShaderManager() {
    Logger::instance().log(Info, "Shader manager created");
}

ShaderManager::~ShaderManager() {
    for (uint32_t i(0) ; i < m_shaders.size() ; ++i) {
        if (m_shaders.is_valid(i)) {
            glDeleteProgram(m_shaders[i].shader_id);
        }
    }

    Logger::instance().log(Info, "Shader manager destroyed");
}

uint32_t ShaderManager::get_shader_openg_gl_id(uint32_t ora_id) {
    return m_shaders[ora_id].shader_id;
}

void ShaderManager::use_shader(uint32_t id) {
    glUseProgram(m_shaders[id].shader_id);
}

uint32_t ShaderManager::load_shader(const std::string& vertex_path, const std::string& fragment_path) {
    // Load shaders source code
    std::string vertex_source_code;
    std::string fragment_source_code;

    if (!shader_load_source(fragment_path, fragment_source_code)) {
        return UNVALID_32;
    }
    if (!shader_load_source(vertex_path, vertex_source_code)) {
        return UNVALID_32;
    }

    // Create shaders
    uint32_t vertex_shader;
    uint32_t fragment_shader;

    if (!shader_create_shader(GL_VERTEX_SHADER, vertex_shader, vertex_source_code)) {
        glDeleteShader(vertex_shader);
        return UNVALID_32;
    }

    if (!shader_create_shader(GL_FRAGMENT_SHADER, fragment_shader, fragment_source_code)) {
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        return UNVALID_32;
    }

    // Create shader program
    uint32_t shader_program;
    if (!shader_create_program(vertex_shader, fragment_shader, shader_program)) {
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        return UNVALID_32;
    }

    // Delete shaders
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    // Create and put the shader in the vector
    uint32_t index = m_shaders.add(Shader{shader_program});
    return index;
}

void ShaderManager::free_shader(uint32_t id) {
    glDeleteProgram(m_shaders[id].shader_id);
    m_shaders.remove(id);
}

bool ShaderManager::shader_load_source(const std::string path, std::string& source) {
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

bool ShaderManager::shader_create_shader(GLenum type, uint32_t& shader_index, const std::string& source) {
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

bool ShaderManager::shader_create_program(uint32_t vertex_shader, uint32_t fragment_shader, uint32_t& shader_program) {
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