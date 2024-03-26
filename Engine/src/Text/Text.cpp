#include "Text/Text.hpp"

namespace eng {

Text::Text()
: m_text(""), m_width(0.0f), m_height(0.0f), m_vao(nullptr), m_vbo(nullptr), m_ibo(nullptr)
{}

Text::~Text() {
    if (m_ibo) { delete m_ibo; }
    if (m_vbo) { delete m_vbo; }
    if (m_vao) { delete m_vao; }
}

void Text::Generate(Font font, const std::string& text) {
    // Delete old data
    if (m_ibo) { delete m_ibo; }
    if (m_vbo) { delete m_vbo; }
    if (m_vao) { delete m_vao; }

    // Initialize
    std::vector<float> vertices(text.size()*16);
    std::vector<uint32_t> indices(text.size()*6);
    m_width = 0.0f;
    m_height = 0.0f;
    m_text = text;

    // Vertices
    int xProg(0);
    for (size_t i(0) ; i < text.size() ; ++i) {
        Character c = font->GetChar(m_text[i]);

        float x(xProg + c.left);
        float y(-c.bh + c.top);

        if (m_height < c.bh) {
            m_height = c.bh;
        }

        vertices[i*16 + 0] = x;         vertices[16*i + 1] = y;         vertices[16*i + 2] = c.x;           vertices[16*i + 3] = c.y + c.h;     // Bottom left
        vertices[i*16 + 4] = x + c.bw;  vertices[16*i + 5] = y;         vertices[16*i + 6] = c.x + c.w;     vertices[16*i + 7] = c.y + c.h;     // Bottom right
        vertices[i*16 + 8] = x + c.bw;  vertices[16*i + 9] = y + c.bh;  vertices[16*i + 10] = c.x + c.w;    vertices[16*i + 11] = c.y;          // Top right
        vertices[i*16 + 12] = x;        vertices[16*i + 13] = y + c.bh; vertices[16*i + 14] = c.x;          vertices[16*i + 15] = c.y;          // Top left

        indices[i*6 + 0] = i*4 + 0;
        indices[i*6 + 1] = i*4 + 1;
        indices[i*6 + 2] = i*4 + 2;

        indices[i*6 + 3] = i*4 + 2;
        indices[i*6 + 4] = i*4 + 3;
        indices[i*6 + 5] = i*4 + 0;

        xProg += c.advance >> 6;
    }
    m_width = xProg;

    // Create the vao, vbo, ibo and layout
    m_vao = new VertexArray;
    m_vao->Bind();
    m_vbo = new VertexBuffer(&vertices[0], vertices.size()*sizeof(float));
    m_ibo = new IndexBuffer(&indices[0], indices.size()*sizeof(uint32_t));

    //VertexAttributesLayout layout = GetTextLayout();

    //m_vao->SetAttributes(*m_vbo, layout);
}

}