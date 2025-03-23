#pragma once

#include <inttypes.h>
#include <memory>
#include <vector>

#include <glad/glad.h>

#include "Log/Logger.hpp"

namespace ora {

class VertexBuffer {
public:

    /// @brief Constructor
    /// @param data Pointer to the first element of the data
    /// @param size Size of the data array in byte
    /// @param static_draw Is the drawing static or not
    /// @warning The size is given in byte not in number of element
    VertexBuffer(const void* data, uint32_t size, bool static_draw = true);

    /// @brief Constructor
    /// @param size Size of the buffer (given in bytes)
    /// @param static_draw Is the drawing static or not
    VertexBuffer(uint32_t size, bool static_draw = true);

    /// @brief Destructor
    ~VertexBuffer();

    /// @brief Bind the vertex array
    void bind() const;

    /// @brief Unbind the vertex array
    void unbind() const;

    /// @brief Update the buffer
    /// @param data Pointer to the beginning of the data
    /// @param size Size of the data
    void update(const void* data, uint32_t size);

    /// @brief Change the capacity of the buffer
    /// @param new_capacity The new capacity
    /// @param conserve_data Are the data conserved
    void change_capacity(uint32_t new_capacity, bool conserve_data);

private:
    /// @brief OpenGL index
    uint32_t m_index;

    uint32_t m_capacity;

    bool m_static_draw;
};

/// @brief Create a vertex buffer from a vector
/// @tparam T Type of the vector
/// @param buffer Vector for the buffer
/// @param static_draw Is the drawing static or not
/// @return A shared pointer to the Vertex Buffer
template<typename T>
std::shared_ptr<VertexBuffer> create_vbo(const std::vector<T>& buffer, bool static_draw = true) {
    return std::make_shared<VertexBuffer>(&buffer.front(), sizeof(T) * buffer.size(), static_draw);
}

template<typename T>
std::shared_ptr<VertexBuffer> create_vbo(uint32_t capacity, bool static_draw = true) {
    return std::make_shared<VertexBuffer>(sizeof(T) * capacity, static_draw);
}

}