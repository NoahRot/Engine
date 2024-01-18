#include "Graphic/IndexBuffer.hpp"

#include <iostream>

namespace eng {

IndexBuffer::IndexBuffer(const void* data, uint32_t size)
: m_index(0)
{
    glCreateBuffers(1, &m_index);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

    std::cout << "INDEX IBO : " << m_index << std::endl;
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &m_index);
}

void IndexBuffer::Bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index);
}

void IndexBuffer::Unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

}