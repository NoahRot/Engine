#pragma once

#include <inttypes.h>
#include <memory>
#include <vector>

#include <glad/glad.h>

namespace ora {

class VertexBuffer {
public:

    /// @brief Constructor
    /// @param data Pointer to the first element of the data
    /// @param size Size of the data array in byte
    /// @warning The size is given in byte not in number of element
    VertexBuffer(const void* data, uint32_t size);

    /// @brief Destructor
    ~VertexBuffer();

    /// @brief Bind the vertex array
    void bind() const;

    /// @brief Unbind the vertex array
    void unbind() const;

private:
    /// @brief OpenGL index
    uint32_t m_index;
};

/// @brief Create a vertex buffer from a vector
/// @tparam T Type of the vector
/// @param buffer Vector for the buffer
/// @return A shared pointer to the Vertex Buffer
template<typename T>
std::shared_ptr<VertexBuffer> create_vbo(const std::vector<T>& buffer) {
    return std::make_shared<VertexBuffer>(&buffer.front(), sizeof(T) * buffer.size());
}

}