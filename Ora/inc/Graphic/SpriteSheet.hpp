#pragma once

#include <inttypes.h>

#include "Graphic/Texture.hpp"
#include "Log/Logger.hpp"

namespace ora {

class SpriteSheet {
public:
    SpriteSheet(uint32_t texture, uint32_t cote, TextureManager* texture_manager);

    uint32_t get_texture() const;

    uint32_t get_nbr_column() const;

    uint32_t get_nbr_row() const;

    uint32_t get_width() const;

    uint32_t get_height() const;

    float get_cote() const;

    void get_uv(uint32_t row, uint32_t column, float& u, float& v) const;

private:
    uint32_t m_texture;
    float m_cote;
    uint32_t m_row;
    uint32_t m_column;
    uint32_t m_width;
    uint32_t m_height;
};

}