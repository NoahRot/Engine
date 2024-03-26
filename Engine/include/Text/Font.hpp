#pragma once

#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H 

#include "Text/Character.hpp"
#include "Core/Core.hpp"
#include "Logger/Logger.hpp"
#include "Graphic/Texture.hpp"
#include "Graphic/VertexArray.hpp"

namespace eng {

class Texture;
class VertexAttributesLayout;
namespace _intern_ {
class _Core;
}

namespace _intern_ {
class Font_ {
public:
    Font_();
    ~Font_();

    bool Load(const std::string& path, uint32_t size, unsigned char beginChar = 0, unsigned char endChar = 128, bool filterLinear = true);

    bool IsValid();

    Character GetChar(char c);

    Texture* GetTexture();

private:
    friend eng::_intern_::_Core;

    static FT_Library s_ftLib;

    bool m_valid;

    FT_Face m_ftFace;

    Texture* m_textureAtlas;
    
    std::map<char, Character> m_charTable;
};
}

typedef eng::_intern_::Font_* Font;

Font CreateFont(const std::string& path, uint32_t size, unsigned char beginChar = 0, unsigned char endChar = 128, bool filterLinear = true);

void DestroyFont(Font font);

/// @brief Standard layout used by font to create the VAO of the text
/// > 3 float, position
/// > 2 float, texture coordinate
/// @return The standard layout
VertexAttributesLayout GetTextLayout();

}