#include "Graphic/VertexArray.hpp"

namespace ora {

VertexArray::VertexArray() 
: m_index(0), m_nbr_attrib(0), m_index_buffer(nullptr)
{
    glGenVertexArrays(1, &m_index);
}

VertexArray::~VertexArray() {
    for (auto buffer : m_vertex_buffers) {
        delete buffer;
    }

    delete m_index_buffer;

    glDeleteVertexArrays(1, &m_index);
}

void VertexArray::bind() const {
    glBindVertexArray(m_index);
}

void VertexArray::unbind() const {
    glBindVertexArray(0);
}

void VertexArray::bind_index() const {
    m_index_buffer->bind();
}

void VertexArray::add_vertex_buffer(VertexBuffer* buffer, const VertexAttribLayout& attrib_layout) {
    // Bind VAO and VBO
    bind();          // Bind the VAO
    buffer->bind();  // Bind the specific VBO

    uint32_t offset = 0;
    
    // Iterate over the layout and configure each attribute
    for (uint32_t i = 0; i < attrib_layout.size(); ++i) {
        const VertexAttributes& va = attrib_layout.get(i);
        
        // Enable the attribute at index i
        glEnableVertexAttribArray(m_nbr_attrib);

        // Configure the attribute pointer
        glVertexAttribPointer(
            m_nbr_attrib,                            // Index of the attribute
            va.size,                      // Number of components
            va.type,                      // Type of data
            va.normalized,                // Normalize flag
            attrib_layout.stride(),       // Stride (space between consecutive attributes)
            (const void*)offset           // Offset within the buffer (from the start of the buffer)
        );

        // Update the offset for the next attribute, if necessary
        offset += va.stride;  // Increment the offset by the attribute's stride
        m_nbr_attrib++;
    }

    // Add the vertex buffer to the list of vertex buffers for this VAO
    m_vertex_buffers.push_back(buffer);
}

void VertexArray::set_index_buffer(IndexBuffer* index_buffer) {
    m_index_buffer = index_buffer;
}

uint32_t VertexArray::get_index_buffer_size() const {
    return m_index_buffer->size();
}

}