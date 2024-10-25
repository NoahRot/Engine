#pragma once

#include <inttypes.h>
#include <vector>

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

    void add_vertex_buffer(VertexBuffer* buffer, const VertexAttribLayout& attrib_layout);

    void set_index_buffer(IndexBuffer* index_buffer);

private:
    uint32_t m_index;

    uint32_t m_nbr_attrib;
    std::vector<VertexBuffer*> m_vertex_buffers;
    IndexBuffer* m_index_buffer;
};

}