#include "Graphic/IndexBuffer.hpp"

namespace ora {

IndexBuffer::IndexBuffer(const uint32_t* data, uint32_t size, bool static_draw) 
: m_index(0), m_size(size)
{
    glGenBuffers(1, &m_index);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index);
    if (static_draw) {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size*sizeof(uint32_t), data, GL_STATIC_DRAW);
    }else{
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size*sizeof(uint32_t), data, GL_DYNAMIC_DRAW);
    }
}

IndexBuffer::IndexBuffer(const std::vector<uint32_t>& data, bool static_draw)
: m_index(0), m_size(data.size())
{
    glGenBuffers(1, &m_index);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index);
    if (static_draw) {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_size*sizeof(uint32_t), &(data[0]), GL_STATIC_DRAW);
    }else{
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_size*sizeof(uint32_t), &(data[0]), GL_DYNAMIC_DRAW);
    }
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &m_index);
}

void IndexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index);
}

void IndexBuffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

uint32_t IndexBuffer::get_count() const {
    return m_size;
}

}