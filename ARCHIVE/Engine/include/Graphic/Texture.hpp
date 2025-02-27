#pragma once

#include <string>
#include <inttypes.h>
#include <vector>

#include <External/glad/glad.h>

#include "Logger/Logger.hpp"
#include "Core/Core.hpp"
#include "Asset/Asset.hpp"

namespace eng {

class Texture_ : public Asset {
public:
    Texture_(uint32_t m_texture_index, int32_t width, int32_t height, int32_t bpp);

    ~Texture_();

    /// @brief Bind the texture to a specific slot (default slot 0)
    /// @param slot The slot in which the texture will be bind (default 0)
    void bind(uint32_t slot = 0);

    /// @brief Unbind the texture
    void unbind();

    /// @brief Get the width of the texture (in ppx)
    /// @return The width of the texture
    int32_t get_width() const;

    /// @brief Get the height of the texture (in ppx)
    /// @return The height of the texture
    int32_t get_height() const;

    /// @brief Get the bit per pixel
    /// @return The number of bit per pixel
    int32_t get_bpp() const;

    /// @brief Get the dimension of the texture
    /// @param w A reference to the width
    /// @param h A reference to the height
    void get_dimensions(int32_t& w, int32_t& h);

    /// @brief Get the index of the texture (for OpenGL)
    /// @return The index of the texture (for OpenGL)
    uint32_t get_texture_index() const;

private:
    /// @brief The index of the texture (for OpenGL)
    uint32_t m_texture_index;

    /// @brief The width of the texture
    int32_t m_width;

    /// @brief The height of the texture
    int32_t m_height;

    /// @brief The number of bit per pixel of the texture
    int32_t m_bpp;
};

typedef Texture_* Texture;

}