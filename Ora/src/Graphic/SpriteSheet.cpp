#include "Graphic/SpriteSheet.hpp"

namespace ora {

SpriteSheet::SpriteSheet(uint32_t texture, uint32_t cote, TextureManager* texture_manager)
: m_texture(texture), m_cote(cote)
{
    const Texture& tex = texture_manager->get_texture(texture);
    m_width = tex.width;
    m_height = tex.height;
    m_row = m_height/cote;
    m_column = m_width/cote;
}

uint32_t SpriteSheet::get_texture() const {
    return m_texture;
}

uint32_t SpriteSheet::get_nbr_column() const {
    return m_column;
}

uint32_t SpriteSheet::get_nbr_row() const {
    return m_row;
}

uint32_t SpriteSheet::get_width() const {
    return m_width;
}

uint32_t SpriteSheet::get_height() const {
    return m_height;
}

float SpriteSheet::get_cote() const {
    return m_cote;
}

void SpriteSheet::get_uv(uint32_t row, uint32_t column, float& u, float& v) const {
    u = m_cote*column/m_width;
    v = m_cote*row/m_height;
}

}