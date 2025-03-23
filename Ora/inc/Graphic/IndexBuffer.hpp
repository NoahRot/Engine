#pragma once

#include <inttypes.h>
#include <vector>
#include <memory>

#include <glad/glad.h>

#include "Log/Logger.hpp"

namespace ora {

class IndexBuffer {
public:

    /// @brief Constructor
    /// @param data Pointer to the first element
    /// @param size Number of elements (given in number of index, not bytes)
    /// @param static_draw Is the drawing static or not
    IndexBuffer(const uint32_t* data, uint32_t size, bool static_draw = true);

    /// @brief Constructor
    /// @param size The size of the buffer (given in number of index, not bytes)
    /// @param static_draw Is the drawing static or not
    IndexBuffer(uint32_t size, bool static_draw = true);

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

    /// @brief Change the data of the buffer
    /// @param data Pointer to the beginning of the data
    /// @param size Number of elements (given in number of index, not bytes)
    void update(const uint32_t* data, uint32_t size);

    /// @brief Change the capacity of the buffer
    /// @param new_capacity The new capacity of the buffer
    /// @param conserve_data Is the old data conserved
    void change_capacity(uint32_t new_capacity, bool conserve_data);

private:
    /// @brief  OpenGL index
    uint32_t m_index;

    /// @brief Number of elements
    uint32_t m_size;

    uint32_t m_capacity;

    bool m_static_draw;
};

inline std::shared_ptr<IndexBuffer> create_ibo(const std::vector<uint32_t>& buffer, bool static_draw = true) {
    return std::make_shared<IndexBuffer>(buffer, static_draw);
}

inline std::shared_ptr<IndexBuffer> create_ibo(uint32_t capacity, bool static_draw = true) {
    return std::make_shared<IndexBuffer>(capacity, static_draw);
}

}