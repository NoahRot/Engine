#pragma once

#include <string>

#include "Tools/Color.hpp"

#include "Text/Character.hpp"
#include "Text/Font.hpp"

#include "Graphic/VertexArray.hpp"
#include "Graphic/VertexBuffer.hpp"
#include "Graphic/IndexBuffer.hpp"

namespace eng {

struct VertexText {
    float x, y, z;      // Position
    float u, v;         // Texture coordinates
    float r, g, b;      // Character color
};

class Text {
public:
    Text(Index font_id);
    Text(Index font_id, const std::string& text, ColorFloat color);
    Text(Index font_id, const std::string& text, const std::vector<ColorFloat>& color);

    void add_text(const std::string& text, ColorFloat color);

    void generate(float depth = 0.0f);

    void erase();

    void bind_font(uint32_t slot = 0);

    std::vector<VertexText>& vertices() { return m_vertices; }
    std::vector<uint32_t>& indices() { return m_indices; }

    float get_width() const { return m_width; }
    float get_height() const { return m_height; }
    std::string get_text() const { return m_text; }

private:
    std::string m_text;
    std::vector<ColorFloat> m_color_char;
    float m_width;
    float m_height;

    std::vector<VertexText> m_vertices;
    std::vector<uint32_t> m_indices;

    Index m_font_id;
};

}