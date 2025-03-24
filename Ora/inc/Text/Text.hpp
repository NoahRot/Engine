#pragma once

#include <string>
#include <vector>
#include <inttypes.h>
#include <memory>

#include "Text/Font.hpp"
#include "Text/Character.hpp"

#include "Graphic/VertexArray.hpp"
#include "Graphic/VertexBuffer.hpp"
#include "Graphic/IndexBuffer.hpp"
#include "Graphic/Layout.hpp"
#include "Graphic/Shader.hpp"

#include "mat/Math.hpp"

namespace ora {

struct VertexText {
    float x, y, z;
    float u, v;
    float r, g, b;
};

class TextRenderer {
public:
    TextRenderer(Font* font, Shader* shader, uint32_t reserve = 1024);

    void submit_text(const std::string& text, mat::Vec2f position, uint8_t r, uint8_t g, uint8_t b);

    void reset();

    void flush();

    void draw();

    Shader* get_shader() const;

    Font* get_font() const;

private:
    Font* m_font;
    Shader* m_shader;

    std::vector<VertexText> m_vertex;
    std::vector<uint32_t> m_index;

    std::shared_ptr<VertexArray> m_vao;
    std::shared_ptr<VertexBuffer> m_vbo;
    std::shared_ptr<IndexBuffer> m_ibo;

    VertexAttribLayout m_text_layout;
};

}