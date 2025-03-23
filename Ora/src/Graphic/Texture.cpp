#include "Graphic/Texture.hpp"

// Using stb_image
#define STB_IMAGE_IMPLEMENTATION
#include "External/stb_image/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "External/stb_image/stb_image_write.h"

namespace ora {
    
Texture::Texture(uint32_t texture_id, int32_t width, int32_t height, int32_t bpp)
: m_texture_id(texture_id), m_width(width), m_height(height), m_bpp(bpp)
{}

Texture::~Texture() {
    glDeleteTextures(1, &m_texture_id);
}

void Texture::bind(int32_t slot) {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

TextureManager::TextureManager(bool pixel_perfect)
:m_pixel_perfect(pixel_perfect)
{
    Logger::instance().log(Info, "Texture manager created");
}

TextureManager::~TextureManager() {
    for (uint32_t i(0) ; i < ORA_MAX_TEXTURE ; ++i) {
        if (m_textures.validity(i)) {
            m_textures.remove(i);
        }
    }

    Logger::instance().log(Info, "Texture manager destroyed");
}

int32_t TextureManager::load_texture(const std::string& file_path) {
    // Read the file from top to bottom
    stbi_set_flip_vertically_on_load(true);

    // Load the image
    int width, height, bpp;
    unsigned char* buffer = stbi_load(file_path.c_str(), &width, &height, &bpp, 4); // 4 because RGBA

    // Generate the texture and bind it
    uint32_t texture_index;
    glGenTextures(1, &texture_index);
    glBindTexture(GL_TEXTURE_2D, texture_index);

    // Set the parameters of the texture
    if (m_pixel_perfect) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }else{
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,  GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,  GL_CLAMP_TO_EDGE);

    // Send the texture to openGL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Check if the buffer contains data
    if (buffer) {
        stbi_image_free(buffer);
    }else{
        Logger::instance().log(Error, "Can't load texture : " + file_path);
        glDeleteTextures(1, &texture_index);
        return -1;
    }

    // Create and add the texture
    int32_t index = m_textures.add(texture_index, width, height, bpp);

    return index;
}

int32_t TextureManager::create_texture(int32_t width, int32_t height, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    std::vector<std::array<unsigned char, 4>> data(width * height, std::array<unsigned char,4>{r, g, b, a});

    // Generate the texture and bind it
    uint32_t texture_index;
    glGenTextures(1, &texture_index);
    glBindTexture(GL_TEXTURE_2D, texture_index);

    // Set the parameters of the texture
    if (m_pixel_perfect) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }else{
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,  GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,  GL_CLAMP_TO_EDGE);

    // Send the texture to openGL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data());
    glBindTexture(GL_TEXTURE_2D, 0);

    // Create and add the texture
    int32_t index = m_textures.add(texture_index, width, height, 4);

    return index;
}

bool TextureManager::free_texture(int32_t index) {
    return m_textures.remove(index);
}

Texture* TextureManager::get_texture(int32_t index) {
    return &m_textures.get(index);
}

bool TextureManager::valid_texture(int32_t index) {
    return m_textures.validity(index);
}

}