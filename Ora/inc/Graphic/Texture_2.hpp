#pragma once

#include <string>
#include <memory>
#include <vector>
#include <array>
#include <stack>
#include <inttypes.h>

#include <ft2build.h>
#include FT_FREETYPE_H 

#include <glad/glad.h>

#include "Memory/DataPool.hpp"

namespace ora2 {

#ifndef ORA_MAX_TEXTURE
    #define ORA_MAX_TEXTURE 1024
#endif

class Texture {
public:
    Texture() = default;

    Texture(uint32_t gl_index, int32_t width, int32_t height, int32_t bpp) 
    : m_gl_index(gl_index), m_width(width), m_height(height), m_bpp(bpp)
    {}

    ~Texture() {
        glDeleteTextures(1, &m_gl_index);
    }

    void bind(uint32_t slot = 0) {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_gl_index);
    }

    void unbind() {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    int32_t width() const {
        return m_width;
    }

    int32_t height() const {
        return m_height;
    }

    int32_t bpp() const {
        return m_bpp;
    }

private:
    uint32_t m_gl_index;
    int32_t m_width;
    int32_t m_height;
    int32_t m_bpp;
};

class TextureManager {
public:
    static int32_t load_texture(const std::string& file_path) {
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
        if (pixel_perfect) {
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
            //Logger::instance().log(Error, "Can't load texture : " + file_path);
            glDeleteTextures(1, &texture_index);
            return -1;
        }

        // Add the texture
        int32_t index = m_textures.add(new Texture(texture_index, width, height, bpp));

        // Check if the texture have been added to the data pool
        if (index < 0) {
            glDeleteTextures(1, &texture_index);
            return -1;
        }

        return index;
    }

    //static Texture create_texture(int32_t width, int32_t height, uint8_t r, uint8_t g, uint8_t b, uint8_t a);

    static Texture& get_texture(uint32_t index) {
        return m_textures[index];
    }

    static bool pixel_perfect;

private:
    TextureManager();

    static DataPool<Texture, ORA_MAX_TEXTURE> m_textures;
};

}