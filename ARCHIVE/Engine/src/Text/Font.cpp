#include "Text/Font.hpp"

FT_Library eng::Font_::s_ft_lib;

namespace eng {


Font_::Font_(const std::map<char, Character>& table_char, Index texture_index, uint32_t size)
: Asset(AssetType::Font), m_table_char(table_char), m_texture_id(texture_index), m_size(size)
{}

Font_::~Font_() {
    AssetManager::instance().unload_asset(m_texture_id);
}

void Font_::bind(uint32_t slot) const {
    AssetManager::instance().get_texture(m_texture_id)->bind();
}

Index Font_::get_texture_index() const { 
    return m_texture_id; 
}

Character& Font_::get_character(char c) { 
    return m_table_char[c]; 
}

uint32_t Font_::get_size() const {
    return m_size;
}

}