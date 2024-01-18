#include "Graphic/VertexArray.hpp"

#include <iostream>

namespace eng {

VertexArray::VertexArray()
: m_index(0)
{
    glGenVertexArrays(1, &m_index);
    std::cout << "INDEX VAO : " << m_index << std::endl;
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_index);
}

void VertexArray::Bind() const {
    glBindVertexArray(m_index);
}

void VertexArray::Unbind() const {
    glBindVertexArray(0);
}

}