#include "Text/Font.hpp"

FT_Library eng::Font_::s_ft_lib;

namespace eng {


Font_::Font_(const std::map<char, Character>& table_char, Index texture_index)
: Asset(AssetType::Font), m_table_char(table_char), m_texture_id(texture_index)
{}

Font_::~Font_() {
    AssetManager::instance().unload_asset(m_texture_id);
}

}