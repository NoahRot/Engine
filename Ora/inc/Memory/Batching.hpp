#pragma once

#include <array>
#include <vector>

#include "Engine/Constant.hpp"
#include "Graphic/VertexArray.hpp"
#include "Graphic/VertexBuffer.hpp"
#include "Graphic/IndexBuffer.hpp"
#include "Graphic/Layout.hpp"

namespace ora {

template<typename V>
class Batch {
public:
    Batch();

    ~Batch();

    void set_shader(uint32_t shader);

    bool add(const std::vector<V>& vertex, const std::vector<uint32_t>& index);

    void clear();

    void generate(VertexAttribLayout layout);

    VertexArray& get_vao() const;

    uint32_t get_shader() const;

private:
    std::array<V,BATCH_MAX_SIZE*4> m_vertex;
    std::array<uint32_t,BATCH_MAX_SIZE*6> m_index;

    uint32_t m_size_vert;
    uint32_t m_size_indi;

    uint32_t m_shader;

    VertexArray* m_vao;
    VertexBuffer* m_vbo;
    IndexBuffer* m_ibo;
};

template<typename V>
Batch<V>::Batch()
: m_size_vert(0), m_size_indi(0), m_shader(UNVALID_32), m_vao(nullptr), m_vbo(nullptr), m_ibo(nullptr)
{}

template<typename V>
Batch<V>::~Batch() {
    clear();
}

template<typename V>
void Batch<V>::set_shader(uint32_t shader) {
    m_shader = shader;
}

template<typename V>
bool Batch<V>::add(const std::vector<V>& vertex, const std::vector<uint32_t>& index) {
    // Check capacity
    if (m_size_vert + vertex.size() >= m_vertex.size() || m_size_indi + index.size() >= m_index.size()) {
        return false;
    }

    // Get offset
    uint32_t offset = m_size_vert;

    // Add vertex
    for (uint32_t i(0) ; i < vertex.size() ; ++i) {
        m_vertex[m_size_vert + i] = vertex[i];
    }

    // Add index
    for (uint32_t i(0) ; i < index.size() ; ++i) {
        m_index[m_size_indi + i] = index[i] + offset;
    }

    m_size_vert += vertex.size();
    m_size_indi += index.size();

    return true;
}

template<typename V>
void Batch<V>::clear() {
    if (m_vao) {
        delete m_vao;

    }else{
        if (m_vbo) {
            delete m_vbo;
        }

        if (m_ibo) {
            delete m_ibo;
        }
    }

    m_vao = nullptr;
    m_vbo = nullptr;
    m_ibo = nullptr;

    m_size_vert = 0;
    m_size_indi = 0;
}

template<typename V>
void Batch<V>::generate(VertexAttribLayout layout) {
    // Clear old data
    if (m_vao) {
        delete m_vao;
    }else{
        if (m_vbo) {
            delete m_vbo;
        }

        if (m_ibo) {
            delete m_ibo;
        }
    }

    // Create the buffers
    
    m_vbo = new VertexBuffer(&m_vertex.front(), sizeof(V)*m_size_vert);
    m_ibo = new IndexBuffer(&m_index.front(), m_size_indi);

    m_vao = new VertexArray;
    m_vao->bind();
    m_vao->add_vertex_buffer(m_vbo, layout);
    m_vao->set_index_buffer(m_ibo);
}

template<typename V>
VertexArray& Batch<V>::get_vao() const {
    return *m_vao;
}

template<typename V>
uint32_t Batch<V>::get_shader() const {
    return m_shader;
}

}