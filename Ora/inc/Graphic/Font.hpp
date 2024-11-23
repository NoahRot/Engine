#pragma once

#include <map>
#include <string>

#include "Graphic/Character.hpp"
#include "Memory/ContinuousVector.hpp"
#include "Log/Logger.hpp"
#include "Engine/UniqueIndex.hpp"
#include "Graphic/Texture.hpp"

#include <glad/glad.h>

#include <ft2build.h>
#include FT_FREETYPE_H 

namespace ora {

struct Font {
    std::map<char, Character> character;
    uint32_t texture;
    uint32_t size;
    uint32_t height;

    //Character get_char(char c) const  {
    //    return character[c];
    //}
};

class FontManager {
public:
    FontManager(TextureManager* texture_manager);

    ~FontManager();

    uint32_t load_font(const std::string& file_path, uint32_t size);

    void free_font(uint32_t font_id);

    Font& get_font(uint32_t font_id);

    void bind_texture(uint32_t fond_id);

    const Character& get_char(uint32_t font_id, char c);

private:
    VectorContinuous<Font> m_font;

    TextureManager* m_texture_manager;

    FT_Library m_ft_lib;
};

}