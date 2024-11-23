#include "Graphic/Font.hpp"

namespace ora {

FontManager::FontManager(TextureManager* texture_manager) 
: m_texture_manager(texture_manager)
{
    // Get logger
    const Logger& logger = Logger::instance();

    // Init freetype
    if (FT_Init_FreeType(&m_ft_lib) != 0) {
        logger.log(Fatal, "Can not initialize FreeType");
        exit(EXIT_FAILURE);
    }

    logger.log(LogLevel::Info, "Font manager created");
}

FontManager::~FontManager() {
    // Free textures atlas
    for (uint32_t i(0) ; i < m_font.size() ; ++i) {
        m_texture_manager->free_texture(m_font[i].texture);
    }

    // Terminate TreeType
    FT_Done_FreeType(m_ft_lib);

    Logger::instance().log(LogLevel::Info, "Font manager destroyed");
}

uint32_t FontManager::load_font(const std::string& file_path, uint32_t size) {
    const Logger& logger = Logger::instance();

    // Load font
    FT_Face face;
    if (FT_New_Face(m_ft_lib, file_path.c_str(), 0, &face))
    {
        logger.log(Error, "Can't load font : " + file_path);
        return UNVALID_32;
    }

    // Set police size
    FT_Set_Pixel_Sizes(face, 0, size);

    // Prepare the size
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Create characters map
    std::map<char, Character> table_character;
    uint32_t atlas_w(0), atlas_h(0);

    for (unsigned char c = 0 ; c < 128 ; ++c) {
        // load character glyph 
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            logger.log(Warning, "Can't load character" + std::to_string((char)c) + " from font " + file_path);
        }

        // Create Character
        table_character[c] = Character{
            0.0f, 0.0f, 0.0f, 0.0f,     // u, v, w, h of the texture
            face->glyph->bitmap.width,  // width
            face->glyph->bitmap.rows,   // rows
            face->glyph->bitmap_left,   // Bearing left
            face->glyph->bitmap_top,    // Bearing right
            face->glyph->advance.x      // Advance
        };

        // Update texture atlas dimensions
        atlas_h = std::max(atlas_h, (uint32_t)face->glyph->bitmap.rows);
        atlas_w += face->glyph->bitmap.width;
    }

    // Create altas texture
    uint32_t texture_id = m_texture_manager->create_texture(atlas_w, atlas_h, 0, 0, 0, 0, false);
    m_texture_manager->bind_texture(texture_id);

    int x_progression(0);
    for (auto& c : table_character) {
        FT_Load_Char(face, c.first, FT_LOAD_RENDER);
        glTexSubImage2D(GL_TEXTURE_2D, 0, x_progression, 0, c.second.bw, c.second.bh, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

        // Set the position and dimension on the texture atlas
        c.second.u = x_progression/(float)atlas_w;
        c.second.w = c.second.bw/(float)atlas_w;
        c.second.h = c.second.bh/(float)atlas_h;

        // Progress
        x_progression += c.second.bw;
    }

    // Create the font
    Font font;
    font.character = table_character;
    font.size = size;
    font.texture = texture_id;
    font.height = atlas_h;

    uint32_t id = m_font.add(font);
    
    return id;
}

void FontManager::free_font(uint32_t font_id) {
    Font& font = m_font[font_id];

    m_texture_manager->free_texture(font.texture);
    m_font.remove(font_id);
}

Font& FontManager::get_font(uint32_t font_id) {
    return m_font[font_id];
}

void FontManager::bind_texture(uint32_t font_id) {
    m_texture_manager->bind_texture(m_font[font_id].texture);
}

const Character& FontManager::get_char(uint32_t font_id, char c) {
    return m_font[font_id].character[c];
}

}