#pragma once

#include <inttypes.h>
#include <vector>

#include <glad/glad.h>

namespace ora {

class IndexBuffer {
public:
    IndexBuffer(const uint32_t* data, uint32_t size_);

    IndexBuffer(const std::vector<uint32_t>& data);

    ~IndexBuffer();

    void bind() const;

    void unbind() const;

    uint32_t size() const;

private:
    uint32_t m_index;
    uint32_t m_size;
};

}