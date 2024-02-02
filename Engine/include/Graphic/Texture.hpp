#pragma once

#include <string>
#include <inttypes.h>
#include <vector>

#include <External/glad/glad.h>

#include "Logger/Logger.hpp"
#include "Core/Core.hpp"

namespace eng {

class Texture {
public:
    Texture();

    ~Texture();

    void Bind(uint32_t slot = 0);

    void Unbind();

    bool Load(const std::string& path, bool filterLinear = true);

    bool IsValid() const;

    int32_t GetWidth() const;

    int32_t GetHeight() const;

    int32_t GetBPP() const;

    void GetDimension(int32_t& w, int32_t& h);

private:
    bool m_valid;
    uint32_t m_textureID;
    int32_t m_width;
    int32_t m_height;
    int32_t m_bpp;
};

}