#pragma once

#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H 

#include "Text/Character.hpp"
#include "Core/Core.hpp"

namespace eng {

namespace _intern_ {
class _Core;
}

class Font {
public:
    Font();
    ~Font();

    bool Load();

    bool IsValid();

private:
    friend eng::_intern_::_Core;

    static FT_Library s_ftLib;

    bool valid;

    FT_Face m_ftFace;

    uint32_t m_texture;

    std::map<char, Character> m_charTable;
};

}