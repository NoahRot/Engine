#include "Graphic/VertexBuffer.hpp"

namespace ora {

VertexBuffer::VertexBuffer(const void* data, uint32_t size, bool static_draw)
: m_index(0), m_capacity(size), m_static_draw(static_draw)
{
    glGenBuffers(1, &m_index);
    glBindBuffer(GL_ARRAY_BUFFER, m_index);
    if (static_draw) {
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }else{
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
    }
}

VertexBuffer::VertexBuffer(uint32_t size, bool static_draw) 
: m_index(0), m_capacity(size), m_static_draw(static_draw)
{
    glGenBuffers(1, &m_index);
    glBindBuffer(GL_ARRAY_BUFFER, m_index);
    if (static_draw) {
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);
    }else{
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    }
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

void VertexBuffer::update(const void* data, uint32_t size) {
    // Resize buffer if necessary
    if (m_capacity < size) {
        if (2*m_capacity < size) {
            change_capacity(size, false);
        }else{
            change_capacity(2*m_capacity, false);
        }
    }
    
    // Update data
    glBindBuffer(GL_ARRAY_BUFFER, m_index);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

void VertexBuffer::change_capacity(uint32_t new_capacity, bool conserve_data) {
    glBindBuffer(GL_ARRAY_BUFFER, m_index);

    if (conserve_data) {
        std::vector<uint32_t> data(m_capacity);
        glGetBufferSubData(GL_ARRAY_BUFFER, 0, m_capacity*sizeof(char), data.data());
        
        if (m_static_draw) {
            glBufferData(GL_ARRAY_BUFFER, new_capacity*sizeof(char), nullptr, GL_STATIC_DRAW);
        }else{
            glBufferData(GL_ARRAY_BUFFER, new_capacity*sizeof(char), nullptr, GL_DYNAMIC_DRAW);
        }

        update(data.data(), std::min(new_capacity, m_capacity));

    }else{
        if (m_static_draw) {
            glBufferData(GL_ARRAY_BUFFER, new_capacity*sizeof(char), nullptr, GL_STATIC_DRAW);
        }else{
            glBufferData(GL_ARRAY_BUFFER, new_capacity*sizeof(char), nullptr, GL_DYNAMIC_DRAW);
        }
    }

    m_capacity = new_capacity;
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

}