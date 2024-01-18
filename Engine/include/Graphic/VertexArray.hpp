#pragma once

#include <External/glad/glad.h>

namespace eng {

class VertexArray {
public:
    VertexArray();

    ~VertexArray();

    void Bind() const;

    void Unbind() const;

private:
    uint32_t m_index;
};

}