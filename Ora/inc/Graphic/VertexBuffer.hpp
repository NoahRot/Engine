#pragma once

#include <inttypes.h>

#include <glad/glad.h>

namespace ora {

class VertexBuffer {
public:
    VertexBuffer(const void* data, uint32_t size);

    ~VertexBuffer();

    void bind() const;

    void unbind() const;

private:
    uint32_t m_index;
};

}