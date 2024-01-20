#pragma once

#include <External/glad/glad.h>

namespace eng {

class IndexBuffer {
public:
    /// @brief Constructor
    /// @param data A pointer to the first element
    /// @param size Size of the buffer (in bytes)
    IndexBuffer(const void* data, uint32_t size);

    /// @brief Destructor
    ~IndexBuffer();

    /// @brief Bind the index buffer
    void Bind() const;

    /// @brief Unbind the index buffer
    void Unbind() const;

private:
    /// @brief The OpenGL index of the index buffer
    uint32_t m_index;
};

}