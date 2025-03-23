#include "Text/Text.hpp"

namespace ora {

TextRenderer::TextRenderer(Font* font, Shader* shader, uint32_t reserve)
: m_font(font), m_shader(shader), m_reserved(reserve), m_vao(nullptr), m_vbo(nullptr), m_ibo(nullptr)
{
    // Create text layout
    m_text_layout.add_float(3); // Add the position
    m_text_layout.add_float(3); // Add the color of the text
    m_text_layout.add_float(2); // Add the texture coordinates

    // Reserve space
    m_vertex.reserve(4 * reserve);
    m_index.reserve(6 * reserve);

    // Create vbo and ibo
    m_vbo = create_vbo<VertexText>(4 * m_reserved, false);
    m_ibo = create_ibo(6 * m_reserved, false);
    m_vao = create_vao();

    m_vao->bind();
    m_vao->add_vertex_buffer(m_vbo, m_text_layout);
    m_vao->set_index_buffer(m_ibo);
    m_vao->unbind();
}

void TextRenderer::submit_text(const std::string& text, mat::Vec2f position, uint8_t r, uint8_t g, uint8_t b) {
    float current_x(0), current_y(0);
    float red(r/255.0f), green(g/255.0f), blue(b/255.0f);

    for (uint32_t i(0) ; i < text.size() ; ++i) {
        if (text[i] == '\n') {
            current_x = 0;
            current_y -= m_font->get_height();

        }else{
            const Character& c = m_font->get_char(text[i]);

            float x_(position[0] + current_x + c.bearing_x);
            float y_(position[1] + current_y - c.height + c.bearing_y);

            uint32_t vert_index = m_vertex.size();

            m_vertex.push_back(VertexText{x_,           y_,             0, red, green, blue,   c.u,        c.v + c.h }); // Bottom left
            m_vertex.push_back(VertexText{x_ + c.width, y_,             0, red, green, blue,   c.u + c.w,  c.v + c.h }); // Bottom right
            m_vertex.push_back(VertexText{x_ + c.width, y_ + c.height,  0, red, green, blue,   c.u + c.w,  c.v       }); // Top right
            m_vertex.push_back(VertexText{x_,           y_ + c.height,  0, red, green, blue,   c.u,        c.v       }); // Top left

            m_index.push_back(vert_index + 0);
            m_index.push_back(vert_index + 1);
            m_index.push_back(vert_index + 2);

            m_index.push_back(vert_index + 2);
            m_index.push_back(vert_index + 3);
            m_index.push_back(vert_index + 0);

            current_x += c.advance >> 6;
        }
    }
}

void TextRenderer::reset() {
    m_vertex.clear();
    m_index.clear();
}

void TextRenderer::flush() {

    m_vbo->bind();
    m_vbo->update(m_vertex.data(), m_vertex.size() * sizeof(VertexText));

    m_ibo->bind();
    m_ibo->update(m_index.data(), m_index.size());
    
}

void TextRenderer::draw() {
    m_shader->use_shader();
    m_font->bind_texture();
    m_vao->bind();
    m_vao->bind_index();

    glDrawElements(GL_TRIANGLES, m_vao->get_index_buffer_size(), GL_UNSIGNED_INT, 0);

    m_vao->unbind();
}

Shader* TextRenderer::get_shader() const {
    return m_shader;
}

Font* TextRenderer::get_font() const {
    return m_font;
}


}