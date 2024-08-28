#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

#include "Logger/Logger.hpp"
#include "Math/Math.hpp"
#include "mat/Math.hpp"

#include "Asset/Asset.hpp"

namespace eng {

class Shader_ : public Asset {
public:
    Shader_(uint32_t shader_program);

    ~Shader_();

    void bind();

    // Set Uniform

    void set_uniform_1i(const std::string& varName, int var) const;
    void set_uniform_1f(const std::string& varName, float var) const;

    void set_uniform_2i(const std::string& varName, int v1, int v2) const;
    void set_uniform_2f(const std::string& varName, float v1, float v2) const;

    void set_uniform_3i(const std::string& varName, int v1, int v2, int v3) const;
    void set_uniform_3f(const std::string& varName, float v1, float v2, float v3) const;

    void set_uniform_4i(const std::string& varName, int v1, int v2, int v3, int v4) const;
    void set_uniform_4f(const std::string& varName, float v1, float v2, float v3, float v4) const;

    void set_uniform_mat3f(const std::string& varName, const math::Mat3f& mat) const;
    void set_uniform_mat4f(const std::string& varName, const math::Mat4f& mat) const;

    void set_uniform_mat3f(const std::string& varName, const mat::Mat3f& mat) const;
    void set_uniform_mat4f(const std::string& varName, const mat::Mat4f& mat) const;

private:
    uint32_t m_shader_program;
};

typedef Shader_* Shader;



namespace _intern_ {

bool shader_load_source(const std::string path, std::string& source);

bool shader_create_shader(GLenum type, uint32_t& shader_index, const std::string& source);

bool shader_create_program(uint32_t vertex_shader, uint32_t fragment_shader, uint32_t& shader_program);

}

}