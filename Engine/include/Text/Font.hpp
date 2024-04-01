#pragma once

#include <map>

#include "Text/Character.hpp"
#include "Core/Core.hpp"
#include "Logger/Logger.hpp"
#include "Graphic/Texture.hpp"
#include "Graphic/VertexArray.hpp"
#include "Asset/AssetManager.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H 

namespace eng {

namespace _intern_{
    class _Core;
}

class Font_ : public Asset {
public:
    Font_(const std::map<char, Character>& table_char, Index texture_index);

    ~Font_();

    Index get_texture_index() const { return m_texture_id; }

    Character& get_character(char c) { return m_table_char[c]; }

    static FT_Library s_ft_lib;

private:
    std::map<char, Character> m_table_char;
    Index m_texture_id;
};

}