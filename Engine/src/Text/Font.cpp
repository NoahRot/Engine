#include "Text/Font.hpp"

FT_Library eng::_intern_::Font_::s_ftLib;

namespace eng {

namespace _intern_ {
Font_::Font_()
: m_valid(false), m_textureAtlas(nullptr)
{}

Font_::~Font_() {
    // Destroy texture
    if (m_textureAtlas) {
        DestroyTexture(m_textureAtlas);
    }

    // Destroy freetype face
    if (m_valid) {
        FT_Done_Face(m_ftFace);
    }
}

bool Font_::Load(const std::string& path, uint32_t size, unsigned char beginChar, unsigned char endChar, bool filterLinear) {
    // Check if the font already exist
    if(m_valid) {
        eng::get_logger().error("Font", "A font is already loaded. Can't overwrite the font");
        return false;
    }

    // Load the font
    if (FT_New_Face(s_ftLib, path.c_str(), 0, &m_ftFace))
    {
        eng::get_logger().error("Font", "Can't load the font. Font path : " + path);
        m_valid = false;
        return false;
    }

    // Use the size for the font
    FT_Set_Pixel_Sizes(m_ftFace, 0, size);  

    // Prepare the size
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Load data and compute the atlas size
    int atlasWidth(0), atlasHeight(0);
    FT_GlyphSlot glyph = m_ftFace->glyph;
    
    for (unsigned char c(0) ; c < 128 ; ++c) {
        if (FT_Load_Char(m_ftFace, c, FT_LOAD_RENDER)) {
            eng::get_logger().error("Font", "Can't load the character " + c);
            m_valid = false;
            FT_Done_Face(m_ftFace);
            return false;
        }

        atlasWidth += glyph->bitmap.width;
        atlasHeight = std::max(atlasHeight, glyph->bitmap.rows);

        // Create the character
        m_charTable[c] = Character{
            0.0f, 0.0f, 0.0f, 0.0f, // x, y, w, h on the texture
            glyph->bitmap.width,    // Width dimension
            glyph->bitmap.rows,     // Height dimension
            glyph->bitmap_left,     // Left bearing
            glyph->bitmap_top,      // Top bearing
            glyph->advance.x        // X advance to the next
        };
    }

    // Create the atlas texture
    m_textureAtlas = CreateTexture(atlasWidth, atlasHeight, true, filterLinear);
    if (!m_textureAtlas) {
        get_logger().error("Font", "Can't create the altas texture");
        m_valid = false;
        return false;
    }

    m_textureAtlas->Bind();

    int xProgression(0);
    for (auto& c : m_charTable) {
        FT_Load_Char(m_ftFace, c.first, FT_LOAD_RENDER);
        glTexSubImage2D(GL_TEXTURE_2D, 0, xProgression, 0, c.second.bw, c.second.bh, GL_RED, GL_UNSIGNED_BYTE, glyph->bitmap.buffer);

        // Set the position and dimension on the texture atlas
        c.second.x = xProgression/(float)atlasWidth;
        c.second.w = c.second.bw/(float)atlasWidth;
        c.second.h = c.second.bh/(float)atlasHeight;

        // Progress
        xProgression += c.second.bw;
    }

    m_valid = true;
    return true;
}

bool Font_::IsValid() {
    return m_valid;
}

Character Font_::GetChar(char c) {
    return m_charTable[c];
}

Texture* Font_::GetTexture() {
    return m_textureAtlas;
}

}

Font CreateFont(const std::string& path, uint32_t size, unsigned char beginChar, unsigned char endChar, bool filterLinear) {
    Font font = new eng::_intern_::Font_;
    font->Load(path, size, beginChar, endChar, filterLinear);

    if (!font->IsValid()) {
        delete font;
        font = nullptr;
    }
    return font;
}

void DestroyFont(Font font) {
    if (font) {
        delete font;
    }
}

VertexAttributesLayout GetTextLayout() {
    eng::VertexAttributesLayout layout;
    layout.AddFloat(3);
    layout.AddFloat(2);

    return layout;
}

}