#include "Text/Font.hpp"

namespace ora {

Font::Font(const std::map<char, Character>& char_map, int32_t texture_id, Texture* texture)
: m_char_map(char_map), m_texture_id(texture_id), m_texture(texture)
{}

Font::~Font()
{}

Character Font::get_char(char c) {
    return m_char_map[c];
}

int32_t Font::get_height() const {
    return m_texture->get_height();
}

int32_t Font::get_texture_id() const {
    return m_texture_id;
}

void Font::bind_texture() {
    m_texture->bind(0);
}







FontManager::FontManager(TextureManager& texture_manager)
: m_texture_manager(texture_manager)
{
    // Get logger
    const Logger& logger = ora::Logger::instance();

    // Init freetype
    if (FT_Init_FreeType(&m_ft_lib) != 0) {
        logger.log(Fatal, "Can not initialize FreeType");
        exit(EXIT_FAILURE);
    }

    logger.log(LogLevel::Info, "Font manager created");
}

FontManager::~FontManager() {
    // Terminate TreeType
    FT_Done_FreeType(m_ft_lib);

    Logger::instance().log(LogLevel::Info, "Font manager destroyed");
}

int32_t FontManager::load_font(const std::string& path, uint32_t font_size) {
    // Get logger
    const Logger& logger = Logger::instance();

    // Get font face
    FT_Face face;
    if (FT_New_Face(m_ft_lib, path.c_str(), 0, &face)) {
        logger.log(Error, "Can not load font : " + path);
        return -1;
    }

    // Set font size
    FT_Set_Pixel_Sizes(face, 0, font_size);

    // Prepare byte size unpacking
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);   

    // Create the characters
    std::map<char, Character> char_map;
    int char_px_space(2);
    int atlas_width(0);
    int atlas_height(0);

    for (unsigned char c(32) ; c < 128 ; ++c) {

        // Load a character
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {    // Check validity
            logger.log(Error, "FreeType Failed to load Glyph : " + c);

        }else{                                          // Create Character
            Character character = {
                0.0f, 0.0f, 0.0f, 0.0f, 
                face->glyph->bitmap.width, face->glyph->bitmap.rows,
                face->glyph->bitmap_left, face->glyph->bitmap_top,
                face->glyph->advance.x
            };

            char_map[c] = character;                    // Set the character in the map

            // Update atlas parameters
            atlas_width += character.width;
            if (c < 128) {
                atlas_width += char_px_space;
            }
            atlas_height = std::max(atlas_height, character.height);
        }
    }

    // Create the font texture atlas
    int32_t texture_id = m_texture_manager.create_texture(atlas_width, atlas_height, 0, 0, 0, 0);
    if (texture_id < 0) {
        FT_Done_Face(face);
        logger.log(Error, "Can not create texture for font");
        return -1;
    }
    Texture* texture = m_texture_manager.get_texture(texture_id);

    // Populate the texture with the characters
    texture->bind();
    int x_progression(0);
    for (auto& c : char_map) {
        FT_Load_Char(face, c.first, FT_LOAD_RENDER);
        glTexSubImage2D(GL_TEXTURE_2D, 0, x_progression, 0, c.second.width, c.second.height, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

        // Set the position and dimension on the texture atlas
        c.second.u = x_progression/(float)atlas_width;
        c.second.w = c.second.width/(float)atlas_width;
        c.second.h = c.second.height/(float)atlas_height;

        // Progress
        x_progression += c.second.width;
    }

    // Free face
    FT_Done_Face(face);

    // Create the font
    return m_fonts.add(char_map, texture_id, texture);
}

bool FontManager::free_font(int32_t index) {
    if (!m_fonts.validity(index)) {
        return false;
    }
    Font& font = m_fonts.get(index);
    m_texture_manager.free_texture(font.get_texture_id());
    return m_fonts.remove(index);
}

Font* FontManager::get_font(int32_t index) {
    return &m_fonts.get(index);
}

bool FontManager::valid_font(int32_t index) {
    return m_fonts.validity(index);
}

}