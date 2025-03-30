#pragma once

#include <array>
#include <vector>

#include <glad/glad.h>

#include <ft2build.h>
#include FT_FREETYPE_H 

#include "Memory/ObjectPool.hpp"
#include "Log/Logger.hpp"

#include "External/stb_image/stb_image_write.h"

namespace ora {

class Texture
{

public:
    Texture(uint32_t texture_id, int32_t width, int32_t height, int32_t bpp);

    ~Texture();

    int32_t get_height() const { return m_height; }

    int32_t get_width() const { return m_width; }

    void bind(int32_t slot = 0);

    void unbind();

private:
    uint32_t m_texture_id;
    int32_t m_width;
    int32_t m_height;
    int32_t m_bpp;
};

#ifndef ORA_MAX_TEXTURE
#define ORA_MAX_TEXTURE 2048
#endif    

class TextureManager {
public:
    TextureManager(bool pixel_perfect);

    ~TextureManager();

    int32_t load_texture(const std::string& file_path);

    int32_t create_texture(int32_t width, int32_t height, uint8_t r, uint8_t g, uint8_t b, uint8_t a);

    bool free_texture(int32_t index);

    Texture* get_texture(int32_t index);

    bool valid_texture(int32_t index);

private:
    ObjectPool<Texture, ORA_MAX_TEXTURE> m_textures;

    bool m_pixel_perfect; 
};

}