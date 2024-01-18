#pragma once

#include <External/glad/glad.h>

namespace eng {

class IndexBuffer {
public:
    IndexBuffer(const void* data, uint32_t size);

    ~IndexBuffer();

    void Bind() const;

    void Unbind() const;

private:
    uint32_t m_index;
};

}