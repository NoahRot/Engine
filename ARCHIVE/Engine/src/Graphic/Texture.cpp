#include "Graphic/Texture.hpp"

// Using stb_image
//#define STB_IMAGE_IMPLEMENTATION
//#include "External/stb_image/stb_image.h"

namespace eng{

Texture_::Texture_(uint32_t m_texture_index, int32_t width, int32_t height, int32_t bpp)
: Asset(AssetType::Texture), m_texture_index(m_texture_index), m_width(width), m_height(height), m_bpp(bpp)
{}

Texture_::~Texture_() {
    glDeleteTextures(1, &m_texture_index);
}

void Texture_::bind(uint32_t slot) {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_texture_index);
}

void Texture_::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

int32_t Texture_::get_width() const {
    return m_width;
}

int32_t Texture_::get_height() const {
    return m_height;
}

int32_t Texture_::get_bpp() const {
    return m_bpp;
}

void Texture_::get_dimensions(int32_t& w, int32_t& h) {
    w = m_width;
    h = m_height;
}

/// @brief Get the index of the texture (for OpenGL)
/// @return The index of the texture (for OpenGL)
uint32_t Texture_::get_texture_index() const {
    return m_texture_index;
}

}