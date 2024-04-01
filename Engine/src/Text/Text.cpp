#include "Text/Text.hpp"

namespace eng {

Text::Text(Index font_id)
: m_width(0), m_height(0), m_font_id(font_id)
{}

Text::Text(Index font_id, const std::string& text, ColorFloat color)
: m_width(0), m_height(0), m_font_id(font_id)
{
    m_text = text;
    m_color_char = std::vector<ColorFloat>(text.size(), color);
}

Text::Text(Index font_id, const std::string& text, const std::vector<ColorFloat>& color)
: m_width(0), m_height(0), m_font_id(font_id)
{
    if (text.size() != color.size()) {
        get_logger().error("Text", "Size of text and color vector different : Text size = " + std::to_string(text.size()) + 
            ", Color size = " + std::to_string(color.size()) + ". Everything initialize to nothing.");
        m_text = "";
        m_color_char = {};
    }else{
        m_text = text;
        m_color_char = color;
    }
    
}

void Text::add_text(const std::string& text, ColorFloat color) {
    // Add text
    m_text += text;

    // Add color
    std::vector<ColorFloat>temp(text.size(), color);
    m_color_char.insert(m_color_char.end(), temp.begin(), temp.end());
}

void Text::generate(float depth) {
    m_vertices = std::vector<VertexText>(m_text.size() * 4);
    m_indices = std::vector<uint32_t>(m_text.size() * 6);
    m_width = 0.0f;
    m_height = 0.0f;

    Font_* font = AssetManager::instance().get_font(m_font_id);

    int x_progression(0);
    for (size_t i(0) ; i < m_text.size() ; ++i) {
        Character& c = font->get_character(m_text[i]);
        ColorFloat color = m_color_char[i];

        float x(x_progression + c.left);
        float y(-c.bh + c.top);

        if (m_height < c.bh) {
            m_height = c.bh;
        }

        m_vertices[i*4 + 0] = VertexText{x,         y,          depth,  c.u,        c.v + c.h,  color.r, color.g, color.b}; // Bottom left
        m_vertices[i*4 + 1] = VertexText{x + c.bw,  y,          depth,  c.u + c.w,  c.v + c.h,  color.r, color.g, color.b}; // Bottom right
        m_vertices[i*4 + 2] = VertexText{x + c.bw,  y + c.bh,   depth,  c.u + c.w,  c.v,        color.r, color.g, color.b}; // Top right
        m_vertices[i*4 + 3] = VertexText{x,         y + c.bh,   depth,  c.u,        c.v,        color.r, color.g, color.b}; // Top left

        m_indices[i*6 + 0] = i*4 + 0;
        m_indices[i*6 + 1] = i*4 + 1;
        m_indices[i*6 + 2] = i*4 + 2;

        m_indices[i*6 + 3] = i*4 + 2;
        m_indices[i*6 + 4] = i*4 + 3;
        m_indices[i*6 + 5] = i*4 + 0;

        x_progression += c.advance >> 6;
    }

    m_width = x_progression;
}

void Text::erase() {
    m_text = "";
    m_color_char = {};
    m_width = 0;
    m_height = 0;

    m_vertices = {};
    m_indices = {};
}

void Text::bind_font(uint32_t slot) {
    AssetManager::instance().get_texture(AssetManager::instance().get_font(m_font_id)->get_texture_index())->bind(slot);
}

}