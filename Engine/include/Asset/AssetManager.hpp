#pragma once

#include "Core/UniqueIndex.hpp"
#include "Core/CoreFnc.hpp"

#include "Tools/Color.hpp"

#include "Asset/Asset.hpp"

#include "Audio/Music.hpp"
#include "Audio/Sound.hpp"

#include "Graphic/Shader.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H 

#include "Text/Font.hpp"
#include "Text/Character.hpp"

#include <map>
#include <iostream>
#include <array>
#include <vector>
#include <map>

namespace eng {

Configuration get_configuration();
class Sound_;
class Music_;
class Texture_;
class Shader_;
struct ShaderSource;
class Font_;

class AssetManager {
public:
    AssetManager(const AssetManager&) = delete;
    AssetManager& operator=(const AssetManager&) = delete;

    ~AssetManager();

    static AssetManager& instance();

    Index load_music(const std::string& path);

    Index load_sound(const std::string& path);

    Index load_texture(const std::string& path, bool pixel_art = get_configuration().tex_pixel_art);

    Index create_texture(uint32_t width, uint32_t height, ColorBit color, bool pixel_art = get_configuration().tex_pixel_art);

    Index load_shader(const std::string& vertex_path, const std::string& fragment_path);

    Index load_font(const std::string& path, uint32_t size);

    void unload_asset(Index index);

    template<typename T>
    T* get_asset(Index index);

    Music_* get_music(Index index);

    Sound_* get_sound(Index index);

    Texture_* get_texture(Index index);

    Shader_* get_shader(Index index);

    Font_* get_font(Index index);

private:
    AssetManager();

    std::map<Index, Asset*> m_table_asset;
};

template<typename T>
T* AssetManager::get_asset(Index index) {
    return static_cast<T*>(m_table_asset[index]);
}

}