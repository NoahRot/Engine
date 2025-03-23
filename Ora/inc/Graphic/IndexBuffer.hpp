#pragma once

#include <inttypes.h>
#include <vector>
#include <memory>

#include <glad/glad.h>

namespace ora {

class IndexBuffer {
public:

    /// @brief Constructor
    /// @param data Pointer to the first element
    /// @param size Number of element
    /// @param static_draw Is the drawing static or not
    IndexBuffer(const uint32_t* data, uint32_t size, bool static_draw = true);

    /// @brief Constructor
    /// @param data Vector of the indices
    /// @param static_draw Is the drawing static or not
    IndexBuffer(const std::vector<uint32_t>& data, bool static_draw = true);

    /// @brief Destructor
    ~IndexBuffer();

    /// @brief Bind the index buffer
    void bind() const;

    /// @brief Unbind the index buffer
    void unbind() const;

    /// @brief Get the number of element in the index buffer
    /// @return The number of element
    uint32_t get_count() const;

private:
    /// @brief  OpenGL index
    uint32_t m_index;

    /// @brief Number of elements
    uint32_t m_size;
};

template<typename T>
std::shared_ptr<IndexBuffer> create_ibo(const std::vector<T>& buffer, bool static_draw = true) {
    return std::make_shared<IndexBuffer>(buffer, static_draw);
}

}