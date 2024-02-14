#pragma once

#include <string>
#include <inttypes.h>
#include <vector>

#include <External/glad/glad.h>

#include "Logger/Logger.hpp"
#include "Core/Core.hpp"

namespace eng {

/// @brief A class that represent a texture used by the engine
class Texture {
public:
    /// @brief Constructor
    Texture();

    /// @brief Destructor
    ~Texture();

    /// @brief Bind the texture to a specific slot (default slot 0)
    /// @param slot The slot in which the texture will be bind (default 0)
    void Bind(uint32_t slot = 0);

    /// @brief Unbind the texture
    void Unbind();

    /// @brief Load a texture from a file
    /// @param path The path of the texture file
    /// @param filterLinear If the texture is filter linearly or to the nearest pixel
    /// when the texture is scaled
    /// @return If the texture has been loaded successfully
    bool Load(const std::string& path, bool filterLinear = true);

    /// @brief Return if the texture is valid
    /// @return If the texture is valid
    bool IsValid() const;

    /// @brief Get the width of the texture (in ppx)
    /// @return The width of the texture
    int32_t GetWidth() const;

    /// @brief Get the height of the texture (in ppx)
    /// @return The height of the texture
    int32_t GetHeight() const;

    /// @brief Get the bit per pixel
    /// @return The number of bit per pixel
    int32_t GetBPP() const;

    /// @brief Get the dimension of the texture
    /// @param w A reference to the width
    /// @param h A reference to the height
    void GetDimension(int32_t& w, int32_t& h);

    /// @brief Get the index of the texture (for OpenGL)
    /// @return The index of the texture (for OpenGL)
    uint32_t GetTextureIndex() const;

private:
    /// @brief If the texture is valid
    bool m_valid;

    /// @brief The index of the texture (for OpenGL)
    uint32_t m_textureID;

    /// @brief The width of the texture
    int32_t m_width;

    /// @brief The height of the texture
    int32_t m_height;

    /// @brief The number of bit per pixel of the texture
    int32_t m_bpp;
};

/// @brief A function to create a texture
/// @param path The path to the file of the texture
/// @param filterLinear If the texture is filter linearly or to the nearest pixel
/// @return A pointer to the texture. It return nullptr if the texture is not valid
Texture* CreateTexture(const std::string& path, bool filterLinear = true);

namespace _intern_ {
/// @brief A class to manage the texture, especially to correctly free the memory
class TextureManager {
public:
    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;

    /// @brief Get the instance of the class
    /// @return The instance of the class
    inline static TextureManager& Instance();

    /// @brief Destructor
    ~TextureManager();

    /// @brief Add a texture when created
    /// @param texture The texture to add
    void AddTexture(Texture* texture);

    /// @brief Remove a texture when destroyed
    /// @param texture The texture to remove
    void RemoveTexture(Texture* texture);

private:
    /// @brief Constructor
    TextureManager();

    /// @brief A list of the textures
    std::map<uint32_t, Texture*> m_textures;
};
}

}