#include "Graphic/VertexBuffer.hpp"

namespace ora {

VertexBuffer::VertexBuffer(const void* data, uint32_t size)
: m_index(0)
{
    glGenBuffers(1, &m_index);
    glBindBuffer(GL_ARRAY_BUFFER, m_index);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &m_index);
}

void VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_index);
}

void VertexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

}