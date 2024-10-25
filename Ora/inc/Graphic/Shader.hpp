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

private:
    VectorContinuous<Shader> m_shaders;

    bool shader_load_source(const std::string path, std::string& source);

    bool shader_create_shader(GLenum type, uint32_t& shader_index, const std::string& source);

    bool shader_create_program(uint32_t vertex_shader, uint32_t fragment_shader, uint32_t& shader_program);
};

}