#include "Graphic/IndexBuffer.hpp"

namespace ora {

IndexBuffer::IndexBuffer(const uint32_t* data, uint32_t size, bool static_draw) 
: m_index(0), m_size(size), m_capacity(size), m_static_draw(static_draw)
{
    glGenBuffers(1, &m_index);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index);
    if (static_draw) {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size*sizeof(uint32_t), data, GL_STATIC_DRAW);
    }else{
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size*sizeof(uint32_t), data, GL_DYNAMIC_DRAW);
    }
}

IndexBuffer::IndexBuffer(uint32_t size, bool static_draw)
: m_index(0), m_size(0), m_capacity(size), m_static_draw(static_draw)
{
    glGenBuffers(1, &m_index);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index);
    if (static_draw) {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size*sizeof(uint32_t), nullptr, GL_STATIC_DRAW);
    }else{
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size*sizeof(uint32_t), nullptr, GL_DYNAMIC_DRAW);
    }
}

IndexBuffer::IndexBuffer(const std::vector<uint32_t>& data, bool static_draw)
: m_index(0), m_size(data.size()), m_capacity(data.size()), m_static_draw(static_draw)
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

void IndexBuffer::update(const uint32_t* data, uint32_t size) {
    // Resize buffer if necessary
    if (m_capacity < size) {
        if (2*m_capacity < size) {
            change_capacity(size, false);
        }else{
            change_capacity(2*m_capacity, false);
        }
    }

    // Update data
    m_size = size;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, size*sizeof(uint32_t), data);
}

void IndexBuffer::change_capacity(uint32_t new_capacity, bool conserve_data) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index);

    if (conserve_data) {
        std::vector<uint32_t> data(m_capacity);
        glGetBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_capacity*sizeof(uint32_t), data.data());
        
        if (m_static_draw) {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, new_capacity*sizeof(uint32_t), nullptr, GL_STATIC_DRAW);
        }else{
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, new_capacity*sizeof(uint32_t), nullptr, GL_DYNAMIC_DRAW);
        }

        if (new_capacity < m_size) {
            m_size = new_capacity;
            update(data.data(), m_size);
        }else{
            update(data.data(), m_size);
        }

    }else{
        if (m_static_draw) {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, new_capacity*sizeof(uint32_t), nullptr, GL_STATIC_DRAW);
        }else{
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, new_capacity*sizeof(uint32_t), nullptr, GL_DYNAMIC_DRAW);
        }
        m_size = 0;
    }

    m_capacity = new_capacity;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

}