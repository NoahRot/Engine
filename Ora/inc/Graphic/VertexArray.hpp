#pragma once

#include <inttypes.h>
#include <vector>
#include <memory>

#include <glad/glad.h>

#include "Graphic/VertexBuffer.hpp"
#include "Graphic/IndexBuffer.hpp"
#include "Graphic/Layout.hpp"

namespace ora {

class VertexArray {
public:
    VertexArray();

    ~VertexArray();

    void bind() const;

    void unbind() const;

    void bind_index() const;

    void add_vertex_buffer(std::shared_ptr<VertexBuffer> buffer, const VertexAttribLayout& attrib_layout);

    void set_index_buffer(std::shared_ptr<IndexBuffer> index_buffer);

    uint32_t get_index_buffer_size() const;

private:
    uint32_t m_index;

    uint32_t m_nbr_attrib;
    std::vector<std::shared_ptr<VertexBuffer>> m_vertex_buffers;
    std::shared_ptr<IndexBuffer> m_index_buffer;
};

inline std::shared_ptr<VertexArray> create_vao() {
    return std::make_shared<VertexArray>();
}

}