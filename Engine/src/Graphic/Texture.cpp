#include "Graphic/Texture.hpp"

// Using stb_image
#define STB_IMAGE_IMPLEMENTATION
#include "External/stb_image/stb_image.h"

namespace eng{

Texture::Texture()
: m_valid(false), m_textureID(0), m_width(0), m_height(0), m_bpp(0)
{
    _intern_::TextureManager::Instance().AddTexture(this);
}

Texture::~Texture() {
    if (m_valid) {
        glDeleteTextures(1, &m_textureID);
    }
    std::cout << "DEBUG : TEXTURE DESTROYED" << std::endl;
}

void Texture::Bind(uint32_t slot) {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void Texture::Unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

bool Texture::Load(const std::string& path, bool filterLinear) {
    // Check if the texture has already loaded data
    if (m_valid) {
        get_logger().error("Texture", "Data already loaded. Can't overwrite data.");
        return false;
    }

    // Read the file from top to bottom
    stbi_set_flip_vertically_on_load(true);

    // Load the image
    unsigned char* buffer = stbi_load(path.c_str(), &m_width, &m_height, &m_bpp, 4); // 4 because RGBA

    // Generate the texture and bind it
    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);

    // Set the parameters of the texture
    if (filterLinear) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }else{
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,  GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,  GL_CLAMP_TO_EDGE);

    // Send the texture to openGL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Check if the buffer contains data
    if (buffer) {
        stbi_image_free(buffer);
        m_valid = true;
    }else{
        get_logger().error("Texture", "Can't load texture : " + path);
        glDeleteTextures(1, &m_textureID);
        m_valid = false;
    }

    return m_valid;
}

bool Texture::Create(uint32_t width, uint32_t height, bool filterLinear, bool alpha) {
    // Check if the texture has already loaded data
    if (m_valid) {
        get_logger().error("Texture", "Data already loaded. Can't overwrite data.");
        return false;
    }

    // Create a buffer of empty data
    uint32_t nbrCanalsPerPixel(3);
    if (alpha) {
        nbrCanalsPerPixel = 4;
    }
    std::vector<unsigned char> buffer(width*height*nbrCanalsPerPixel, 0);

    // Generate the texture and bind it
    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);

    // Set the parameters of the texture
    if (filterLinear) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }else{
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,  GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,  GL_CLAMP_TO_EDGE);

    // Send the texture to openGL
    if (alpha) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &buffer.front());
    }else{
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, &buffer.front());
    }
    glBindTexture(GL_TEXTURE_2D, 0);

    m_valid = true;

    return true;
}

bool Texture::IsValid() const {
    return m_valid;
}

int32_t Texture::GetWidth() const {
    return m_width;
}

int32_t Texture::GetHeight() const {
    return m_height;
}

int32_t Texture::GetBPP() const {
    return m_bpp;
}

void Texture::GetDimension(int32_t& w, int32_t& h) {
    w = m_width;
    h = m_height;
}

uint32_t Texture::GetTextureIndex() const {
    return m_textureID;
}






Texture* CreateTexture(const std::string& path, bool filterLinear) {
    Texture* texture = new Texture;
    texture->Load(path, filterLinear);
    if (!texture->IsValid()) {
        delete texture;
        texture = nullptr;
    }
    return texture;
}

Texture* CreateTexture(uint32_t width, uint32_t height, bool alpha, bool filterLinear) {
    Texture* texture = new Texture;
    texture->Create(width, height, alpha, filterLinear);
    if (!texture->IsValid()) {
        delete texture;
        texture = nullptr;
    }
    return texture;
}

void DestroyTexture(Texture* texture) {
    eng::_intern_::TextureManager::Instance().RemoveTexture(texture);
}





namespace _intern_ {

TextureManager::TextureManager(){
    std::cout << "DEBUG : TextureManager created" << std::endl;
}

TextureManager::~TextureManager() {
    for (auto tex : m_textures) {
        std::cout << "DEBUG : TEXTURE MANAGER : " << tex.second << std::endl;
        if (tex.second != nullptr) {
            delete tex.second;
        }
    }
    std::cout << "DEBUG : TextureManager destroyed" << std::endl;
}

TextureManager& TextureManager::Instance() {
    static TextureManager s_instance;
    return s_instance;
}

void TextureManager::AddTexture(Texture* texture) {
    m_textures[texture->GetTextureIndex()] = texture;
}

void TextureManager::RemoveTexture(Texture* texture) {
    m_textures[texture->GetTextureIndex()] = nullptr;
    delete texture;
}

}

}