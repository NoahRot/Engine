#pragma once

#include <inttypes.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include <glad/glad.h>

#include "Log/Logger.hpp"
#include "Memory/ObjectPool.hpp"

#include "mat/Math.hpp"

namespace ora {

class Shader {
public:

    /// @brief Constructor
    /// @param index OpenGL index
    Shader(int32_t index);

    /// @brief Destructor
    ~Shader();

    /// @brief Use the shader for draw
    void use_shader() const;

    /// @brief Get the map of the uniform
    /// @return A constant reference to the map of uniform
    const std::unordered_map<std::string, int>& get_uniform_map() const;

    /// @brief Check the validity of a uniform variable name
    /// @param var_name Name of the variable
    /// @return True if the name is valid, False otherwise
    bool uniform_validity(const std::string& var_name) const;

    // Set the uniform variables

    void set_1i(const std::string& var_name, int var);
    void set_1f(const std::string& var_name, float var);
    void set_1d(const std::string& var_name, double var);

    void set_2i(const std::string& var_name, const mat::Vec2i& var);
    void set_2f(const std::string& var_name, const mat::Vec2f& var);
    void set_2d(const std::string& var_name, const mat::Vec2d& var);

    void set_3i(const std::string& var_name, const mat::Vec3i& var);
    void set_3f(const std::string& var_name, const mat::Vec3f& var);
    void set_3d(const std::string& var_name, const mat::Vec3d& var);

    void set_4i(const std::string& var_name, const mat::Vec4i& var);
    void set_4f(const std::string& var_name, const mat::Vec4f& var);
    void set_4d(const std::string& var_name, const mat::Vec4d& var);

    void set_mat3f(const std::string& var_name, const mat::Mat3f& var);
    void set_mat3d(const std::string& var_name, const mat::Mat3d& var);

    void set_mat4f(const std::string& var_name, const mat::Mat4f& var);
    void set_mat4d(const std::string& var_name, const mat::Mat4d& var);

private:
    /// @brief Map linking the name of the variables and the location
    std::unordered_map<std::string, int> m_uniform_map;

    /// @brief OpenGL index of the shader
    uint32_t m_index;
};

#ifndef ORA_MAX_SHADER
#define ORA_MAX_SHADER 128
#endif

class ShaderManager {
public:

    /// @brief Constructor
    ShaderManager();

    /// @brief Destructor
    ~ShaderManager();

    /// @brief Load a shader
    /// @param vertex_path Path to the vertex source code
    /// @param fragment_path Path to the fragment source code
    /// @return The index of the shader. Return -1 if a problem occured
    int32_t load_shader(const std::string& vertex_path, const std::string& fragment_path);

    /// @brief Free a shader
    /// @param index The index of the shader
    /// @return True if the process was successful
    bool free_shader(int32_t index);

    /// @brief Get a shader
    /// @param index The index of the shader
    /// @return A pointer to the shader
    Shader* get_shader(int32_t index);

    /// @brief Check if the index is valid
    /// @param index The index of a shader
    /// @return True if the index is valid
    bool valid_shader(int32_t index);

private:

    /// @brief Load a source code to a string
    /// @param path Path of the source code
    /// @param source A variable for the return source code
    /// @return True if the precess succeded
    bool load_source(const std::string path, std::string& source);

    /// @brief Create a shader from a source code
    /// @param type Type of shader to create
    /// @param shader_index A variable to return the index of the shader
    /// @param source The source code of the shader
    /// @return True if the precess succeded
    bool create_shader(GLenum type, uint32_t& shader_index, const std::string& source);

    /// @brief Create a program by combining vertex and fragment shader
    /// @param vertex_shader Index of the vertex shader
    /// @param fragment_shader Index of the fragment shader
    /// @param shader_program Variable to return the program index
    /// @return True if the precess succeded 
    bool create_program(uint32_t vertex_shader, uint32_t fragment_shader, uint32_t& shader_program);

    /// @brief A pool to contain all shaders
    ObjectPool<Shader, ORA_MAX_SHADER> m_shaders;
};

}