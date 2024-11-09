#pragma once

#include <inttypes.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <glad/glad.h>

#include "Log/Logger.hpp"
#include "Memory/ContinuousVector.hpp"
#include "Engine/UniqueIndex.hpp"

#include "mat/Math.hpp"

namespace ora {

struct Shader {
    uint32_t shader_id;
};

class ShaderManager {
public:
    ShaderManager();

    ~ShaderManager();

    uint32_t get_shader_openg_gl_id(uint32_t ora_id);

    void use_shader(uint32_t id);

    uint32_t load_shader(const std::string& vertex_path, const std::string& fragment_path);

    void free_shader(uint32_t id);

    void set_unif_1f(uint32_t id, const std::string& var_name, float var) {
        int location = glGetUniformLocation(m_shaders[id].shader_id, var_name.c_str());
        glUniform1f(location, var);
    }

    void set_unif_2f(uint32_t id, const std::string& var_name, const mat::Vec2f& var) {
        int location = glGetUniformLocation(m_shaders[id].shader_id, var_name.c_str());
        glUniform2f(location, var[0], var[1]);
    }

    void set_unif_3f(uint32_t id, const std::string& var_name, const mat::Vec3f& var) {
        int location = glGetUniformLocation(m_shaders[id].shader_id, var_name.c_str());
        glUniform3f(location, var[0], var[1], var[2]);
    }

    void set_unif_4f(uint32_t id, const std::string& var_name, const mat::Vec4f& var) {
        int location = glGetUniformLocation(m_shaders[id].shader_id, var_name.c_str());
        glUniform4f(location, var[0], var[1], var[2], var[3]);
    }

    void set_unif_1i(uint32_t id, const std::string& var_name, int var) {
        int location = glGetUniformLocation(m_shaders[id].shader_id, var_name.c_str());
        glUniform1i(location, var);
    }

    void set_unif_2i(uint32_t id, const std::string& var_name, const mat::Vec2i& var) {
        int location = glGetUniformLocation(m_shaders[id].shader_id, var_name.c_str());
        glUniform2i(location, var[0], var[1]);
    }

    void set_unif_3i(uint32_t id, const std::string& var_name, const mat::Vec3i& var) {
        int location = glGetUniformLocation(m_shaders[id].shader_id, var_name.c_str());
        glUniform3i(location, var[0], var[1], var[2]);
    }

    void set_unif_4i(uint32_t id, const std::string& var_name, const mat::Vec4i& var) {
        int location = glGetUniformLocation(m_shaders[id].shader_id, var_name.c_str());
        glUniform4i(location, var[0], var[1], var[2], var[3]);
    }

    void set_unif_mat3f(uint32_t id, const std::string& var_name, const mat::Mat3f& mat) {
        int location = glGetUniformLocation(m_shaders[id].shader_id, var_name.c_str());
        glUniformMatrix3fv(location, 1, false, &mat(0,0));
    }

    void set_unif_mat4f(uint32_t id, const std::string& var_name, const mat::Mat4f& mat) {
        int location = glGetUniformLocation(m_shaders[id].shader_id, var_name.c_str());
        glUniformMatrix4fv(location, 1, false, &mat(0,0));
    }

private:
    VectorContinuous<Shader> m_shaders;

    bool shader_load_source(const std::string path, std::string& source);

    bool shader_create_shader(GLenum type, uint32_t& shader_index, const std::string& source);

    bool shader_create_program(uint32_t vertex_shader, uint32_t fragment_shader, uint32_t& shader_program);
};

}