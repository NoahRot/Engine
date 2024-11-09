#pragma once

#include <array>

#include <glad/glad.h>

#include <ft2build.h>
#include FT_FREETYPE_H 

#include "Memory/ContinuousVector.hpp"
#include "Log/Logger.hpp"
#include "Engine/UniqueIndex.hpp"

namespace ora {

struct Texture
{
    uint32_t texture_id;
    int32_t width;
    int32_t height;
    int32_t bpp;
};
    

class TextureManager {
public:
    TextureManager(bool pixel_perfect);

    ~TextureManager();

    uint32_t load_texture(const std::string& file_path, bool pixel_perfect);

    uint32_t create_texture(int32_t width, int32_t height, uint8_t r, uint8_t g, uint8_t b, uint8_t a, bool pixel_perfect);

    void free_texture(uint32_t id);

    void bind_texture(uint32_t id, int32_t slot = 0);

    void unbind_texture();

    uint32_t get_texture_openg_gl_id(uint32_t ora_id);

private:
    VectorContinuous<Texture> m_textures;

    bool m_pixel_perfect; 
};

}