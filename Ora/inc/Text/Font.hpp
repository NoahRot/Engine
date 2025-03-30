#pragma once

#include <map>
#include <string>
#include <algorithm>

#include "Text/Character.hpp"
#include "Memory/ObjectPool.hpp"
#include "Log/Logger.hpp"
#include "Graphic/Texture.hpp"

#include <glad/glad.h>

#include <ft2build.h>
#include FT_FREETYPE_H 

namespace ora {

class Font {
public:
    Font(const std::map<char, Character>& char_map, int32_t texture_id, Texture* texture);

    ~Font();

    Character get_char(char c);

    int32_t get_height() const;

    int32_t get_texture_id() const;

    void bind_texture();

private:
    std::map<char, Character> m_char_map;
    int32_t m_texture_id; 
    Texture* m_texture; 
};

#ifndef ORA_MAX_FONT
#define ORA_MAX_FONT 64
#endif

class FontManager {
public:
    FontManager(TextureManager& texture_manager);

    ~FontManager();

    int32_t load_font(const std::string& path, uint32_t font_size);

    bool free_font(int32_t index);

    Font* get_font(int32_t index);

    bool valid_font(int32_t index);

private:
    FT_Library m_ft_lib;

    ObjectPool<Font, ORA_MAX_FONT> m_fonts;

    TextureManager& m_texture_manager;
};

}