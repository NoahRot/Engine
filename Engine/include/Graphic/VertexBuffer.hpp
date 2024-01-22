#pragma once

#include <vector>

#include <External/glad/glad.h>

#include "Graphic/Buffer.hpp"

namespace eng {

class VertexBuffer {
public:
    /// @brief Constructor
    /// @param data A pointer to the first element
    /// @param size Size of the buffer (in bytes)
    VertexBuffer(const void* data, uint32_t size);

    /// @brief Destructor
    ~VertexBuffer();

    /// @brief Bind the vertex buffer
    void Bind() const;

    /// @brief Unbind the vertex buffer
    void Unbind() const;

private:
    /// @brief The OpenGL index of the vertex buffer
    uint32_t m_index;
};

}